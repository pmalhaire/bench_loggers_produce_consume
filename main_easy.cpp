#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include <iostream>

#define ELPP_THREAD_SAFE 1
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

constexpr auto MESSAGE_COUNT = 1000000ul;

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

void produceThreadEasy()
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

void consumeThreadEasy()
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

void produce_consume_easy()
{
    std::thread t1(produceThreadEasy);
    std::thread t2(consumeThreadEasy);
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
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info,
                    el::ConfigurationType::Format, "%datetime %level %msg");
    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);
    LOG(INFO) << "Main"
              << "start";

    LOG(INFO) << "Main"
              << "produce consume log stdio";
    auto start = std::chrono::system_clock::now();
    produce_consume_std_io();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_easy_stdio = end - start;

    LOG(INFO) << "Main"
              << "let the CPU rest a bit";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG(INFO) << "Main"
              << "produce consume log easy all";
    start = std::chrono::system_clock::now();
    produce_consume_easy();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_easy_all = end - start;

    LOG(INFO) << "Main"
              << "let the CPU rest a bit";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG(INFO) << "Main"
              << "produce consume log easy only main";
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Warning,
                    el::ConfigurationType::Format, "%datetime %level %msg");
    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);

    start = std::chrono::system_clock::now();
    produce_consume_easy();
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff_easy_main_only = end - start;
    std::cout << "Main:"
              << "stdio messages consumed:" << MESSAGE_COUNT << " in " << diff_easy_stdio.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_easy_stdio.count() << "msg/s" << std::endl;
    std::cout << "Main:"
              << "easy_all messages consumed:" << MESSAGE_COUNT << " in " << diff_easy_all.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_easy_all.count() << "msg/s" << std::endl;
    ;
    std::cout << "Main:"
              << "easy_main_only messages consumed:" << MESSAGE_COUNT << " in " << diff_easy_main_only.count() << "s"
              << " rate:" << MESSAGE_COUNT / diff_easy_main_only.count() << "msg/s" << std::endl;
    ;

    return 0;
}