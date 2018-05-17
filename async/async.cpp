// async.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <dbgmsg.h>
#include <future>


int main()
{
    std::future<int> fut1 = std::async(std::launch::async, []()
    {
        return 8;
    });

    DBGMSG(_T("%d"), fut1.get());
    //////////////////////////////////////////////////////////////////////////
    std::future<int> fut2 = std::async(std::launch::async, []()
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        return 8;
    });

    DBGMSG(_T("waiting..."));

    std::future_status stat;
    do
    {
        stat = fut2.wait_for(std::chrono::seconds(1));

        switch (stat)
        {
        case std::future_status::ready:
            DBGMSG(_T("ready."));
            break;
        case std::future_status::timeout:
            DBGMSG(_T("timeout."));
            break;
        case std::future_status::deferred:
            DBGMSG(_T("deferred."));
            break;
        default:
            break;
        }
    } while (stat != std::future_status::ready);

    DBGMSG(_T("result is %d."), fut2.get());

    return 0;
}

