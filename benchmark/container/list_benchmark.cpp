// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <list>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include "forfun/container/list.hpp"

TEST_CASE(
    "Linked list benchmarking",
    "[benchmark][container][list][dynamic_allocation]"
)
{
    ankerl::nanobench::Bench()
        .title("Linked list")
        .relative(true)

        .run(
            "::std::list<int>",
            [] -> void {
                std::list<int> list{};
                list.push_back(1301);

                auto const r{list.back()};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            "experimental::container::list",
            [] -> void {
                forfun::experimental::container::list list{};
                list.push_back(1301);

                auto const r{list.back()};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
