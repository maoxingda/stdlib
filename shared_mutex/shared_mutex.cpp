// shared_mutex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <mutex>            // For std::unique_lock
#include <shared_mutex>
#include <thread>
#include <dbgmsg.h>

class ThreadSafeCounter
{
public:
    ThreadSafeCounter() = default;

    // Multiple threads/readers can read the counter's value at the same time.
    unsigned int get() const
    {
        std::shared_lock<std::shared_mutex> lock(m_mtx);
        return m_value;
    }

    // Only one thread/writer can increment/write the counter's value.
    void increment()
    {
        std::unique_lock<std::shared_mutex> lock(m_mtx);
        m_value++;
    }

    // Only one thread/writer can reset/write the counter's value.
    void reset()
    {
        std::unique_lock<std::shared_mutex> lock(m_mtx);
        m_value = 0;
    }

private:
    unsigned int m_value = 0;
    mutable std::shared_mutex m_mtx;
};

int main()
{
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]()
    {
        for (int i = 0; i < 3; i++)
        {
            counter.increment();

            DBGMSG(_T("%d %d"), std::this_thread::get_id(), counter.get());

            // Note: Writing to std::cout actually needs to be synchronized as well
            // by another std::mutex. This has been omitted to keep the example small.
        }
    };

    std::thread thrd1(increment_and_print);
    std::thread thrd2(increment_and_print);

    thrd1.join();
    thrd2.join();
}

// Explanation: The output below was generated on a single-core machine. When
// thread1 starts, it enters the loop for the first time and calls increment()
// followed by get(). However, before it can print the returned value to
// std::cout, the scheduler puts thread1 to sleep and wakes up thread2, which
// obviously has time enough to run all three loop iterations at once. Back to
// thread1, still in the first loop iteration, it finally prints its local copy
// of the counter's value, which is 1, to std::cout and then runs the remaining
// two loop iterations. On a multi-core maschine, none of the threads is put to
// sleep and the output is more likely to be in ascending order.