// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/single_number.hpp"
#include "forfun_c/single_number.h"

TEST_CASE("Single number benchmarking", "[benchmark][single_number]")
{
    using namespace forfun::single_number;

    std::vector const nums{
        // clang-format off
        1,  1,  2,  2,  3,  3,  4,   4,
        5,  5,  6,  6,  7,  7,  8,   8,
        9,  9,  10, 10, 11, 11, 12,  12,
        13, 13, 14, 14, 15, 15, 101,
        // clang-format off
    };

    ankerl::nanobench::Bench()

        .title("Single number")
        .relative(true)

        .run(
            NAMEOF_RAW(functional::get_single<std::vector<int> const&>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{functional::get_single(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(imperative::get_single<std::vector<int> const&>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{imperative::get_single(nums)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(::forfun_get_single).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    ::forfun_get_single(nums.data(), nums.size())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
