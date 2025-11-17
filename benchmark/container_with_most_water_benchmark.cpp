// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/container_with_most_water.hpp"

TEST_CASE(
    "Container with most water benchmarking",
    "[benchmark][container_with_most_water]"
)
{
    using namespace forfun::container_with_most_water;

    using CIter = std::array<int, 32>::const_iterator;

    constexpr std::array const input{
        2,   4,  6,  8,  10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 257,
        257, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9,  7,  5,  3,  1,
    };

    ankerl::nanobench::Bench()

        .title("Container with most water")
        .relative(true)

        .run(
            NAMEOF_RAW(brute::calc_max_area<CIter, CIter>).c_str(),
            [&input] noexcept -> void {
                auto const volatile r{
                    brute::calc_max_area(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(enhanced::calc_max_area<CIter, CIter>).c_str(),
            [&input] noexcept -> void {
                auto const volatile r{
                    enhanced::calc_max_area(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
