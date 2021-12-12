#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include <iostream>

// spdlogger
#include "spdlog/sinks/stdout_sinks.h"

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

auto mainLog = spdlog::stdout_logger_st("main");
auto produceLog = spdlog::stdout_logger_st("produce");
auto consumeLog = spdlog::stdout_logger_st("consume");

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

void produceThreadSpd()
{
    produceLog->info("start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        produceLog->info("Produce one i:{}", i);
        syncQueue.push(i);
    }
}

void consumeThreadSpd()
{
    consumeLog->info("start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        consumeLog->info("Consume one {}", elem);
    }
}

void produce_consume_spd()
{
    std::thread t1(produceThreadSpd);
    std::thread t2(consumeThreadSpd);
    t1.join();
    t2.join();
}

void produceThreadStdIO()
{
    produceLog->info("start");
    for (auto i = 0; i < MESSAGE_COUNT; i++)
    {
        std::cout << "Produce one " << i << std::endl;
        syncQueue.push(i);
    }
}

void consumeThreadStdIO()
{
    consumeLog->info("start");
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
    mainLog->info("start");

    mainLog->info("produce consume log stdio");
    auto start = std::chrono::system_clock::now();
    produce_consume_std_io();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_spd_stdio = end - start;

    mainLog->info("let the CPU rest a bit");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mainLog->info("produce consume log spd all");
    start = std::chrono::system_clock::now();
    produce_consume_spd();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_spd_all = end - start;

    mainLog->info("let the CPU rest a bit");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mainLog->info("produce consume log spd only main");
    produceLog->set_level(spdlog::level::warn);
    consumeLog->set_level(spdlog::level::warn);
    start = std::chrono::system_clock::now();
    produce_consume_spd();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_spd_main_only = end - start;

    mainLog->info(
        "stdio messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_spd_stdio.count(), MESSAGE_COUNT / diff_spd_stdio.count());
    mainLog->info(
        "spd all messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_spd_all.count(), MESSAGE_COUNT / diff_spd_all.count());
    mainLog->info(
        "spd main only messages consumed:{} in {}s rate:{}msg/s",
        MESSAGE_COUNT, diff_spd_main_only.count(), MESSAGE_COUNT / diff_spd_main_only.count());

    return 0;
}