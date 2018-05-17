// mutex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <mutex>


int main()
{
    std::mutex mtx;
    std::recursive_mutex rmtx;
    std::recursive_timed_mutex rtmtx;
    std::timed_mutex tmtx;

    std::lock_guard<decltype(mtx)> lock1(mtx);
    std::lock_guard<decltype(rmtx)> lock2(rmtx);
    std::lock_guard<decltype(rtmtx)> lock3(rtmtx);
    std::lock_guard<decltype(tmtx)> lock4(tmtx);

    //std::lock(mtx, rmtx, rtmtx, tmtx);

    std::unique_lock<decltype(rmtx)> lock5(rmtx);
    return 0;
}

