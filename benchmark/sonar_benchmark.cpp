// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sonar.hpp"

TEST_CASE("sonar benchmarking", "[benchmark][sonar]")
{
    using namespace forfun::sonar;

    Sonar const sonar{{
        // clang-format off
        {.x = 0, .y = 7},
        {.x = 2, .y = 5},
        {.x = 3, .y = 3},
        {.x = 4, .y = 6},
        {.x = 5, .y = 2},
        // clang-format on
    }};

    ankerl::nanobench::Bench()

        .title("forfun::sonar")
        .relative(true)

        .run(
            NAMEOF(count_ships).c_str(),
            [&sonar]() {
                ankerl::nanobench::doNotOptimizeAway(count_ships(
                    sonar, {.top = 0, .bottom = 5, .left = 2, .right = 7}));
            })

        ;
}
