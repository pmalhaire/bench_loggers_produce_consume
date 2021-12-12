#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include <iostream>

// fmtlogger
#define FMTLOG_HEADER_ONLY 1
#define FMT_HEADER_ONLY 1
#include "fmtlog.h"
// #include "fmtlog-inl.h"

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

void produceThreadFmt()
{
    fmtlog::setThreadName("produce");
    logi("start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        logi("Produce one i:{}", i);
        syncQueue.push(i);
    }
}

void consumeThreadFmt()
{
    fmtlog::setThreadName("consume");
    logi("start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        logi("Consume one {}", elem);
    }
}

void produce_consume_fmt()
{
    std::thread t1(produceThreadFmt);
    std::thread t2(consumeThreadFmt);
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
    fmtlog::setThreadName("main");
    logi("start");

    logi("produce consume log stdio");
    auto start = std::chrono::system_clock::now();
    produce_consume_std_io();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_fmt_stdio = end - start;

    logi("let the CPU rest a bit");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    logi("produce consume log fmt all");
    start = std::chrono::system_clock::now();
    produce_consume_fmt();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_fmt_all = end - start;

    logi("let the CPU rest a bit");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    logi("produce consume log fmt only main");
    fmtlog::setLogLevel(fmtlog::WRN);
    start = std::chrono::system_clock::now();
    produce_consume_fmt();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_fmt_main_only = end - start;

    fmtlog::setLogLevel(fmtlog::INF);
    logi(
        "stdio messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_fmt_stdio.count(), MESSAGE_COUNT / diff_fmt_stdio.count());
    logi(
        "fmt all messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_fmt_all.count(), MESSAGE_COUNT / diff_fmt_all.count());
    logi(
        "fmt main only messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_fmt_main_only.count(), MESSAGE_COUNT / diff_fmt_main_only.count());
    fmtlog::poll();
    return 0;
}