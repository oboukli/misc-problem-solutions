// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sorting/insertion_sort.hpp"

TEST_CASE("insertion_sort benchmarking", "[benchmark][sorting][insertion_sort]")
{
    using ContainerType = std::array<int, 512>;

    ankerl::nanobench::Bench()

        .title("Insertion sort")
        .relative(true)

        .run(
            NAMEOF_RAW(forfun::sorting::insertion_sort<ContainerType::iterator>)
                .c_str(),
            []() {
                ContainerType arr{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
                forfun::sorting::insertion_sort(arr.begin(), arr.end());

                ankerl::nanobench::doNotOptimizeAway(arr);
            })

        ;
}
