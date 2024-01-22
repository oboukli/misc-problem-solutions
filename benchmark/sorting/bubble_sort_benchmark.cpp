// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sorting/bubble_sort.hpp"

TEST_CASE("bubble_sort benchmarking", "[benchmark][sorting][bubble_sort]")
{
    using namespace forfun::sorting;
    using ContainerType = std::array<int, 16>;
    using Itr = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("Bubble sort")
        .relative(true)

        .run(
            NAMEOF_RAW(plain::bubble_sort<Itr>).c_str(),
            []() {
                ContainerType arr{
                    9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6};
                plain::bubble_sort(arr.begin(), arr.end());

                ankerl::nanobench::doNotOptimizeAway(arr);
            })

        .run(NAMEOF_RAW(stl::bubble_sort<Itr>).c_str(), []() {
            ContainerType arr{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6};
            stl::bubble_sort(arr.begin(), arr.end());

            ankerl::nanobench::doNotOptimizeAway(arr);
        });
}
