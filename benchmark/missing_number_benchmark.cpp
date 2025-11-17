// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/missing_number.hpp"

namespace {

using RangeType = std::vector<int> const&;

} // namespace

TEST_CASE("Missing number benchmarking", "[benchmark][missing_number]")
{
    using namespace forfun::missing_number;

    std::vector const nums{
        14, 1, 16, 6, 8, 4, 5, 15, 2, 9, 13, 3, 10, 7, 0, 12
    };

    ankerl::nanobench::Bench()

        .title("Missing number")
        .relative(true)

        .run(
            NAMEOF_RAW(bitwise::find_missing_number<RangeType>).c_str(),
            [&nums] noexcept -> void {
                auto const volatile r{bitwise::find_missing_number(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(functional::find_missing_number<RangeType>).c_str(),
            [&nums] noexcept -> void {
                auto const volatile r{functional::find_missing_number(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(imperative::find_missing_number<RangeType>).c_str(),
            [&nums] noexcept -> void {
                auto const volatile r{imperative::find_missing_number(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(optimized::find_missing_number<RangeType>).c_str(),
            [&nums] noexcept -> void {
                auto const volatile r{optimized::find_missing_number(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
