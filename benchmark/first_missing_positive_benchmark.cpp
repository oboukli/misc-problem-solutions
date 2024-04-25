// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <tuple>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/first_missing_positive.hpp"

TEST_CASE(
    "forfun::first_missing_positive benchmarking",
    "[benchmark][first_missing_positive]")
{
    using namespace forfun::first_missing_positive;

    using ContainerType = std::array<int, 128>;
    using Itr = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("Lowest missing positive integer")
        .relative(true)

        .run(
            NAMEOF_RAW(base::lowest_missing<Itr>).c_str(),
            []() {
                std::array nums{
                    // clang-format off
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    // clang-format on
                };
                static_assert(nums.size() == std::tuple_size_v<ContainerType>);

                auto const r{base::lowest_missing(nums.begin(), nums.end())};

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(fast::lowest_missing<Itr>).c_str(),
            []() {
                std::array nums{
                    // clang-format off
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    9, 8, 7, 6, 5, 4, 3, 2, 1, -1,
                    0, 0, 0, 0, 0, 0, 0, 0,
                    // clang-format on
                };
                static_assert(nums.size() == std::tuple_size_v<ContainerType>);

                auto const r{fast::lowest_missing(nums.begin(), nums.end())};

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
