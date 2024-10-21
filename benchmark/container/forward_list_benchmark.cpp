// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <forward_list>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include "forfun/container/forward_list.hpp"

TEST_CASE(
    "Forward list benchmarking",
    "[benchmark][container][forward_list][dynamic_allocation]"
)
{
    ankerl::nanobench::Bench()

        .title("Forward list")
        .relative(true)

        .run(
            "::std::forward_list<int>",
            []() {
                ::std::forward_list<int> forward_list{};
                forward_list.push_front(1301);

                auto const r{forward_list.front()};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            "forfun::experimental::container::forward_list<std::integral T>",
            []() {
                forfun::experimental::container::forward_list<int>
                    forward_list{};
                forward_list.push_front(1301);

                auto const r{forward_list.front()};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
