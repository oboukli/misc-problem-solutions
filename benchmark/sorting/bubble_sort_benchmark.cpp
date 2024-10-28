// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <tuple>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sorting/bubble_sort.hpp"

TEST_CASE("Bubble sort benchmarking", "[benchmark][sorting][bubble_sort]")
{
    using namespace forfun::sorting;

    using ContainerType = std::array<int, 16U>;
    using Itr = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("Bubble sort")
        .relative(true)

        .run(
            NAMEOF_RAW(plain::bubble_sort<Itr, Itr>).c_str(),
            []() noexcept {
                ContainerType nums{
                    9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6
                };
                static_assert(nums.size() == std::tuple_size_v<ContainerType>);

                plain::bubble_sort(nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            }
        )

        .run(NAMEOF_RAW(stl::bubble_sort<Itr, Itr>).c_str(), []() noexcept {
            ContainerType nums{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6};
            static_assert(nums.size() == std::tuple_size_v<ContainerType>);

            stl::bubble_sort(nums.begin(), nums.end());

            ankerl::nanobench::doNotOptimizeAway(nums);
        });
}
