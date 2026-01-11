// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cmath>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/common/math.hpp"

TEST_CASE("Integer division ceiling benchmarking", "[benchmark][math]")
{
    using namespace forfun::common;

    ankerl::nanobench::Bench()

        .title("Integer division ceiling")
        .relative(true)

        .run(
            "::std::ceil(double)",
            [] noexcept -> void {
                auto const volatile r{static_cast<int>(std::ceil(
                    double{std::numeric_limits<int>::max()}
                    / double{std::numeric_limits<int>::max() - 1}
                ))};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(math::div_ceil).c_str(),
            [] noexcept -> void {
                auto const volatile r{math::div_ceil(
                    std::numeric_limits<int>::max(),
                    std::numeric_limits<int>::max() - 1
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
