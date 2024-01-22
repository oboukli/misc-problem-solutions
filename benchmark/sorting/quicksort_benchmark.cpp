// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sorting/quicksort.hpp"

TEST_CASE("quicksort benchmarking", "[benchmark][sorting][quicksort]")
{
    using namespace forfun::sorting;
    using ContainerType = std::array<int, 16>;
    using Itr = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("Quicksort")
        .relative(true)

        .run(
            NAMEOF_RAW(quicksort<Itr>).c_str(),
            []() {
                ContainerType arr{
                    9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6};
                quicksort(arr.begin(), arr.end());

                ankerl::nanobench::doNotOptimizeAway(arr);
            })

        ;
}
