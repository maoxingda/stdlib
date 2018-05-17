// condition_variable.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <dbgmsg.h>

std::mutex              g_mtx;
std::condition_variable g_cv;
std::wstring            g_data;
bool g_ready            = false;
bool g_processed        = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lock(g_mtx);
    g_cv.wait(lock, [] { return g_ready; });

    // after the wait, we own the lock.
    DBGMSG(_T("Worker thread is processing data"));
    g_data += L" after processing";

    // Send data back to main()
    g_processed = true;
    DBGMSG(_T("Worker thread signals data processing completed"));

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lock.unlock();
    g_cv.notify_one();
}

int main()
{
    std::thread worker(&worker_thread);

    g_data = L"Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lock(g_mtx);
        g_ready = true;
        DBGMSG(_T("signals data ready for processing"));
    }
    g_cv.notify_one();

    // wait for the worker
    {
        std::unique_lock<std::mutex> lock(g_mtx);
        g_cv.wait(lock, [] {return g_processed;});
    }
    DBGMSG(_T("Back in, data = %s."), g_data.c_str());

    worker.join();
}