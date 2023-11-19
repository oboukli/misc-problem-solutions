// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

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

    ankerl::nanobench::Bench()

        .title("Lowest missing positive integer")
        .relative(true)

        .run(
            NAMEOF_RAW(cast::lowest_missing<ContainerType>).c_str(),
            []() {
                ContainerType a{
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

                auto r{forfun::first_missing_positive::cast::lowest_missing(a)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(span::lowest_missing<ContainerType>).c_str(),
            []() {
                ContainerType a{
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

                auto r{forfun::first_missing_positive::span::lowest_missing(a)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
