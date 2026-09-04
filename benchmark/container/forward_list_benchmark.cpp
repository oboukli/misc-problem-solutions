// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <forward_list>

#include <catch2/catch_test_macros.hpp>

#include <nameof.hpp>

#include <nanobench.h>

#include "forfun/container/forward_list.hpp"

TEST_CASE(
    "Forward list benchmarking",
    "[benchmark][container][forward_list][dynamic_allocation]"
)
{
    ankerl::nanobench::Bench()

        .title("Forward list construct push front")
        .relative(true)

        .run(
            NAMEOF_TYPE(::std::forward_list<int>).c_str(),
            [] -> void {
                ::std::forward_list<int> forward_list{};
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);

                auto const r{forward_list.front()};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_TYPE(forfun::container::forward_list<int>).c_str(),
            [] -> void {
                forfun::container::forward_list<int> forward_list{};
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);
                forward_list.push_front(1301);

                auto const r{forward_list.front()};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}

TEST_CASE(
    "Reverse forward list benchmarking",
    "[container][forward_list][dynamic_allocation][reverse_forward_list]"
)
{
    std::forward_list<int> std_forward_list;
    std_forward_list.push_front(1381);
    std_forward_list.push_front(1399);
    std_forward_list.push_front(1409);
    std_forward_list.push_front(1423);
    std_forward_list.push_front(1427);
    std_forward_list.push_front(1429);
    std_forward_list.push_front(1433);
    std_forward_list.push_front(1439);
    std_forward_list.push_front(1447);
    std_forward_list.push_front(1451);
    std_forward_list.push_front(1453);
    std_forward_list.push_front(1459);
    std_forward_list.push_front(1471);
    std_forward_list.push_front(1481);
    std_forward_list.push_front(1483);
    std_forward_list.push_front(1487);

    forfun::container::forward_list<int> forfun_forward_list{};
    forfun_forward_list.push_front(1381);
    forfun_forward_list.push_front(1399);
    forfun_forward_list.push_front(1409);
    forfun_forward_list.push_front(1423);
    forfun_forward_list.push_front(1427);
    forfun_forward_list.push_front(1429);
    forfun_forward_list.push_front(1433);
    forfun_forward_list.push_front(1439);
    forfun_forward_list.push_front(1447);
    forfun_forward_list.push_front(1451);
    forfun_forward_list.push_front(1453);
    forfun_forward_list.push_front(1459);
    forfun_forward_list.push_front(1471);
    forfun_forward_list.push_front(1481);
    forfun_forward_list.push_front(1483);
    forfun_forward_list.push_front(1487);

    ankerl::nanobench::Bench()

        .title("Reverse forward list")
        .relative(true)

        .run(
            NAMEOF_TYPE(::std::forward_list<int>).c_str(),
            [&std_forward_list] noexcept -> void { std_forward_list.reverse(); }
        )

        .run(
            NAMEOF_TYPE(forfun::container::forward_list<int>).c_str(),
            [&forfun_forward_list] noexcept -> void {
                forfun_forward_list.reverse();
            }
        )

        ;
}
