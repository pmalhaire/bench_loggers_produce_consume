#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stdexcept>

#include "spdlog/sinks/stdout_sinks.h"

using namespace std;

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

auto mainLog = spdlog::stdout_logger_st("main");
auto produceLog = spdlog::stdout_logger_st("produce");
auto consumeLog = spdlog::stdout_logger_st("consume");

constexpr auto MESSAGE_COUNT = 10;
int consumed = 0;

void produceThread()
{
    produceLog->info("start");
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        g_ready = true;
        ul.unlock();
        produceLog->info("Produce one i:{}", i);
        g_cv.notify_one();
    }
}

void consumeThread()
{
    consumeLog->info("start");
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        g_cv.wait(ul, [] { return g_ready; });
        consumeLog->info("Consuming one");
        consumed++;
    }
}

int main()
{
    mainLog->info("started");
    std::thread t1(produceThread);
    std::thread t2(consumeThread);
    t1.join();
    t2.join();
    while (consumed < MESSAGE_COUNT)
    {
        mainLog->info("wait for end");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mainLog->info("consumed:{}", consumed);
    }
    mainLog->info("consumed:{}", consumed);
    return 0;
}