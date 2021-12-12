#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>
#include <queue>
#include "spdlog/sinks/stdout_sinks.h"

using namespace std;

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

auto mainLog = spdlog::stdout_logger_st("main");
auto produceLog = spdlog::stdout_logger_st("produce");
auto consumeLog = spdlog::stdout_logger_st("consume");

constexpr auto MESSAGE_COUNT = 1000000;
int consumed = 0;

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
    produceLog->info("start");
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        produceLog->info("Produce one i:{}", i);
        syncQueue.push(i);
    }
}

void consumeThread()
{
    consumeLog->info("start");
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        auto elem = syncQueue.pop();
        consumeLog->info("Consuming one {}", elem);
        consumed++;
    }
}

int main()
{
    mainLog->info("started");
    auto start = std::chrono::system_clock::now();
    std::thread t1(produceThread);
    std::thread t2(consumeThread);
    while (consumed < MESSAGE_COUNT)
    {
        mainLog->info("wait for end");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mainLog->info("consumed:{}", consumed);
    }
    t1.join();
    t2.join();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    mainLog->info("consumed:{} in {}s rate:{}msg/s", consumed, diff.count(), consumed / diff.count());
    return 0;
}