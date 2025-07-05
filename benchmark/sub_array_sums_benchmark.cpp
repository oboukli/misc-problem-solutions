// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/sub_array_sums.hpp"

TEST_CASE(
    "Sum of all subarrays of size K benchmarking", "[benchmark][sub_array_sums]"
)
{
    using namespace forfun::sub_array_sums;

    static constexpr std::array const numbers{
        // clang-format off
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8,
        // clang-format on
    };
    std::array<int, 8> sums{};

    ankerl::nanobench::Bench()

        .title("Sum of all subarrays of size K")
        .relative(true)

        .run(
            NAMEOF_RAW(sum_each<std::array<int, 64>, std::array<int, 8>>)
                .c_str(),
            [&sums]() noexcept {
                decltype(numbers)::size_type const volatile sub_size{8U};
                sum_each(numbers, sums, sub_size);

                ankerl::nanobench::doNotOptimizeAway(sums);
            }
        )

        ;
}
