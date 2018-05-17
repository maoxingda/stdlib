// atomic.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <atomic>
#include <cassert>

int main()
{
    std::atomic_bool ready = false;

    assert(ready.is_lock_free());

    std::atomic_int  count = 0;

    assert(count.is_lock_free());

    ++count;
    --count;
    count += 1;
    count -= 1;
}

