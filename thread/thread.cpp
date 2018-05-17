// thread.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <thread>
#include <mutex>


int main()
{
    std::this_thread::yield();
    std::thread::id curid = std::this_thread::get_id();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));

    std::timed_mutex tmtx;
    tmtx.try_lock_for(std::chrono::seconds(2));
    tmtx.try_lock_until(std::chrono::system_clock::now() + std::chrono::seconds(2));

    std::recursive_mutex rmtx;
    std::lock_guard<decltype(rmtx)> lg1(rmtx);
    std::lock_guard<decltype(rmtx)> lg2(rmtx);
    return 0;
}

