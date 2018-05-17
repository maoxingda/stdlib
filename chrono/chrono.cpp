// chrono.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <chrono>
#include <dbgmsg.h>

long fibonacci(unsigned n)
{
    if (n < 2)
    {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> stt, end;

    stt = std::chrono::system_clock::now();

    DBGMSG(_T("f(42) = %d"), fibonacci(42));

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - stt;

    DBGMSG(_T("finished computation and elapsed %f seconds."), elapsed_seconds.count());
}