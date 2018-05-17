// call_once.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <dbgmsg.h>
#include <mutex>


std::once_flag g_of1;

void call_once()
{
    DBGMSG(_T("This is a test of function std.call_once."));
}

void thread_func()
{
    std::call_once(std::ref(g_of1), call_once);
}

int main()
{
    std::thread thrd1(thread_func);
    std::thread thrd2(thread_func);

    thrd1.join();
    thrd2.join();

    return 0;
}

