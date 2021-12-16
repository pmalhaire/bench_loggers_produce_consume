#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include <iostream>

#include "quill/Quill.h"

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

constexpr auto MESSAGE_COUNT = 1000000ul;
constexpr auto loggerName = "quill";

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
auto lvl = quill::LogLevel::Info;

void produceThread()
{
    quill::Logger *log(quill::create_logger("produce"));
    log->set_log_level(lvl);
    LOG_INFO(log, "start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        LOG_INFO(log, "Produce one i:{}", i);
        syncQueue.push(i);
    }
    // delete log;
}

void consumeThread()
{
    quill::Logger *log(quill::create_logger("consume"));
    log->set_log_level(lvl);
    LOG_INFO(log, "start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        LOG_INFO(log, "Consume one {}", elem);
    }
    // delete log;
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
    quill::enable_console_colours();
    quill::start();

    quill::Logger *logger = quill::get_logger();
    logger->set_log_level(quill::LogLevel::TraceL3);

    // enable a backtrace that will get flushed when we log CRITICAL
    logger->init_backtrace(2, quill::LogLevel::Critical);

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

    // set logger to warning
    lvl = quill::LogLevel::Warning;

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