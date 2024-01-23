// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sub_array_sums.hpp"

TEST_CASE("sub_array_sums benchmarking", "[benchmark][sub_array_sums]")
{
    using namespace forfun::sub_array_sums;

    ankerl::nanobench::Bench()

        .title("Sum of all subarrays of size K")

        .run(
            NAMEOF_RAW(
                // clang-format off
                sum_each<std::array<int, 6>,
                    std::array<int, 4>,
                    std::array<int, 6>::size_type>)
                // clang-format on
                .c_str(),
            []() {
                static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
                static std::array<int, 4> sums{};
                static constexpr std::array<int, 6>::size_type const sub_size{
                    3};

                sum_each(numbers, sums, sub_size);

                ankerl::nanobench::doNotOptimizeAway(sums);
            })

        ;
}
