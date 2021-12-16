#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include <iostream>
#include <memory>

#include <string>
#define G3_DYNAMIC_LOGGING 1
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <g3log/logmessage.hpp>
#include <g3log/loglevels.hpp>

struct CustomSink
{

    // Linux xterm color
    // http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
    enum FG_Color
    {
        YELLOW = 33,
        RED = 31,
        GREEN = 32,
        WHITE = 97
    };

    FG_Color GetColor(const LEVELS level) const
    {
        if (level.value == WARNING.value)
        {
            return YELLOW;
        }
        if (level.value == DEBUG.value)
        {
            return GREEN;
        }
        if (g3::internal::wasFatal(level))
        {
            return RED;
        }

        return WHITE;
    }

    void ReceiveLogMessage(g3::LogMessageMover logEntry)
    {
        auto level = logEntry.get()._level;
        auto color = GetColor(level);

        std::cout << "\033[" << color << "m"
                  << logEntry.get().toString() << "\033[m" << std::endl;
    }
};

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

constexpr auto MESSAGE_COUNT = 1000000ul;
constexpr auto loggerName = "g3log";

template <typename T>
class SynchronizedQueue
{
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condvar_;

    typedef std::lock_guard<std::mutex> lock;
    typedef std::unique_lock<std::mutex> ulock;

public:
    void push(T const &val)
    {
        lock l(mutex_);             // prevents multiple pushes corrupting queue_
        bool wake = queue_.empty(); // we may need to wake consumer
        queue_.push(val);
        if (wake)
            condvar_.notify_one();
    }

    T pop()
    {
        ulock u(mutex_);
        while (queue_.empty())
            condvar_.wait(u);
        // now queue_ is non-empty and we still have the lock
        T retval = queue_.front();
        queue_.pop();
        return retval;
    }
};

SynchronizedQueue<int> syncQueue;

void produceThread()
{
    LOG(INFO) << "produce:"
              << "Produce start";
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        LOG(INFO) << "produce:"
                  << "Produce one " << i;
        syncQueue.push(i);
    }
}

void consumeThread()
{
    LOG(INFO) << "consume:"
              << "Consume start";
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        LOG(INFO) << "consume:"
                  << "Consume one " << elem;
    }
}

void produce_consume()
{
    std::thread t1(produceThread);
    std::thread t2(consumeThread);
    t1.join();
    t2.join();
}

void produceThreadStdIO()
{
    std::cout << "Produce start" << std::endl;
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        std::cout << "Produce one " << i << std::endl;
        syncQueue.push(i);
    }
}

void consumeThreadStdIO()
{
    std::cout << "Consume start" << std::endl;
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        std::cout << "Consume one " << elem << std::endl;
    }
}

void produce_consume_std_io()
{
    std::thread t1(produceThreadStdIO);
    std::thread t2(consumeThreadStdIO);
    t1.join();
    t2.join();
}

int main()
{
    // initialize the logger before it can receive LOG calls
    auto worker = g3::LogWorker::createLogWorker();

    auto handle = worker->addSink(std::make_unique<CustomSink>(),
                                  &CustomSink::ReceiveLogMessage);
    g3::initializeLogging(worker.get());

    std::cerr << "produce consume log stdio" << std::endl;
    auto start = std::chrono::system_clock::now();
    produce_consume_std_io();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_stdio = end - start;

    std::cerr << "let the CPU rest a bit" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cerr << "produce consume log all" << std::endl;
    start = std::chrono::system_clock::now();
    produce_consume();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_all = end - start;

    std::cerr << "let the CPU rest a bit" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cerr << "produce consume log none" << std::endl;

    start = std::chrono::system_clock::now();
    produce_consume();
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff_none = end - start;
    std::cerr << "stdio messages consumed:" << MESSAGE_COUNT << " in " << diff_stdio.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_stdio.count() << "msg/s" << std::endl;
    std::cerr << loggerName << ":all messages consumed:" << MESSAGE_COUNT << " in " << diff_all.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_all.count() << "msg/s" << std::endl;
    std::cerr << loggerName << ":none messages consumed:" << MESSAGE_COUNT << " in " << diff_none.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_none.count() << "msg/s" << std::endl;
    return 0;
}