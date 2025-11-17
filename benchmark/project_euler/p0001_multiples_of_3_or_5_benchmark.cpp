// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"

TEST_CASE(
    "Multiples of three or five benchmarking",
    "[benchmark][p0001_multiples_of_3_or_5]"
)
{
    using namespace forfun::project_euler::multiples_of_3_or_5;

    ankerl::nanobench::Bench()

        .title("Multiples of three or five")
        .relative(true)

        .run(
            NAMEOF_RAW(find_sum_mult_three_five).c_str(),
            [] noexcept -> void {
                auto const volatile input{999U};
                auto const volatile r{find_sum_mult_three_five(input)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
