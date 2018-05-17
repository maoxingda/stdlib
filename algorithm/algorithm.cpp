// algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <dbgmsg.h>


// std.adjacent_find
void adjacent_find()
{
    std::vector<int> iv = { 1, 2, 3, 3, 4, 5 };

    // use default predicate(std.equal_to)
    auto iter1 = std::adjacent_find(std::begin(iv), std::end(iv));

    if (std::end(iv) != iter1)
    {
        DBGMSG(_T("The two adjacent element are (%d, %d)."), *iter1, *(iter1 + 1));
    }

    // use custom predicate(lambda expression)
    auto cus_pred = [](int lhs, int rhs)
    {
        return (lhs < rhs);
    };

    auto iter2 = std::adjacent_find(std::begin(iv), std::end(iv), cus_pred);

    if (std::end(iv) != iter2)
    {
        DBGMSG(_T("The two adjacent element satisfy custom predicate are (%d, %d)."), *iter2, *(iter2 + 1));
    }
}

// std.all_of
void all_of()
{
    std::vector<int> iv = { 1, 2, 3, 3, 4, 5 };

    auto greater_than_zero = [](int elem)
    {
        return 0 < elem;
    };

    auto cond = std::all_of(std::begin(iv), std::end(iv), greater_than_zero);

    if (cond)
    {
        DBGMSG(_T("All of the elements are greater than zero."));
    }
}

// std.any_of
void any_of()
{
    std::vector<int> iv = { -1, 2, 3, 3, 4, 5 };

    auto less_than_zero = [](int elem)
    {
        return 0 > elem;
    };

    auto cond = std::any_of(std::begin(iv), std::end(iv), less_than_zero);

    if (cond)
    {
        DBGMSG(_T("There is existed at least one of the element are less than zero."));
    }
}

// std.binary_search
void binary_search()
{
    std::vector<int> iv = { -1, 2, 3, 3, 4, 5 };

    auto cond = std::binary_search(std::begin(iv), std::end(iv), 3);

    if (cond)
    {
        DBGMSG(_T("There is existed the element with the value of 3."));
    }
}

// std.copy
void copy()
{
    std::vector<int> iv1 = { -1, 2, 3, 3, 4, 5 };

    std::vector<int> iv2;

    std::copy(std::begin(iv1), std::end(iv1), std::back_inserter(iv2));

    if (iv1 == iv2)
    {
        DBGMSG(_T("copy succeed."));
    }
}

int main()
{
    adjacent_find();
    all_of();
    any_of();
    binary_search();
    copy();

    return 0;
}

