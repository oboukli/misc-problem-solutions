// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/common/math.hpp"

TEST_CASE("Integer division ceiling benchmarking", "[benchmark][math]")
{
    using namespace forfun::common::math;

    ankerl::nanobench::Bench()

        .title("Integer division ceiling")
        .relative(true)

        .run(
            NAMEOF_RAW(alternative::div_ceil).c_str(),
            [] noexcept -> void {
                auto const volatile r{alternative::div_ceil(
                    std::numeric_limits<int>::max(),
                    std::numeric_limits<int>::max() - 1
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(core::div_ceil).c_str(),
            [] noexcept -> void {
                auto const volatile r{core::div_ceil(
                    std::numeric_limits<int>::max(),
                    std::numeric_limits<int>::max() - 1
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
