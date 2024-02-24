// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sonar.hpp"

TEST_CASE("sonar benchmarking", "[benchmark][sonar]")
{
    using namespace forfun::sonar;

    Sonar const sonar{{{0, 7}, {2, 5}, {3, 3}, {4, 6}, {5, 2}}};

    ankerl::nanobench::Bench()

        .title("forfun::sonar")
        .relative(true)

        .run(
            NAMEOF(count_ships).c_str(),
            [&sonar]() {
                ankerl::nanobench::doNotOptimizeAway(
                    count_ships(sonar, {0, 5, 2, 7}));
            })

        ;
}
