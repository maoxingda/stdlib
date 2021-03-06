// promise.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <thread>
#include <future>
#include <chrono>
#include <numeric>


void accumulate(std::list<int>::iterator first,
    std::list<int>::iterator last,
    std::promise<int> accumulate_promise)
{
    accumulate_promise.set_value(std::accumulate(first, last, 0));
}

void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    barrier.set_value();
}

int main()
{
    std::list<int> numberrs = { 1, 2, 3, 4, 5 };

    std::promise<int> accumulate_promise;
    std::future<int> accumulate_futrue = accumulate_promise.get_future();

    std::thread work_thread(accumulate, numberrs.begin(), numberrs.end(), std::move(accumulate_promise));

    accumulate_futrue.wait();

    printf("sum = %d. \r\n", accumulate_futrue.get());

    getchar();

    return 0;
}

