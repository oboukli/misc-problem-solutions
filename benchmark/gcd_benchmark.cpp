// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cmath>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/gcd.hpp"

TEST_CASE("gcd benchmarking", "[benchmark][gcd]")
{
    using namespace forfun::gcd::euclid::recursive;

    ankerl::nanobench::Bench()

        .title("Greatest common divisor")
        .relative(true)

        .run(
            NAMEOF(gcd).c_str(),
            []() {
                int const volatile m{1 << 25};
                int const volatile n{(1 << 15) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(gcd(m, n));
            })

        ;
}
