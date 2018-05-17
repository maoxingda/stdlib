// condition_variable_predicate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <dbgmsg.h>

std::condition_variable cv;
std::mutex              g_mtx;  // This mutex is used for three purposes:
                                // 1) to synchronize accesses to i
                                // 2) to synchronize accesses to std::cerr
                                // 3) for the condition variable cv
bool g_ready            = false;

void waits()
{
    std::unique_lock<std::mutex> lock(g_mtx);

    DBGMSG(_T("Waiting..."));

    cv.wait(lock, [] { return g_ready; });

    DBGMSG(_T("...finished waiting. g_ready == %d"), g_ready);
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(g_mtx);

        DBGMSG(_T("Notifying..."));
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lock(g_mtx);

        g_ready = true;

        DBGMSG(_T("Notifying again..."));
    }
    cv.notify_all();
}

int main()
{
    std::thread thrd1(&waits), thrd2(&waits), thrd3(&waits), thrd4(&signals);

    thrd1.join(), thrd2.join(), thrd3.join(), thrd4.join();
}