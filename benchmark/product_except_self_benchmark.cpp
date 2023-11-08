// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/product_except_self.hpp"

using ContainerType = std::array<int, 128>;
inline constexpr ContainerType const nums{
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,
    4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
    13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,
    3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
};

TEST_CASE(
    "product_except_self benchmarking", "[benchmark][product_except_self]")
{
    using namespace forfun::product_except_self;

    using Itr = ContainerType::iterator;

    ContainerType actual;

    ankerl::nanobench::Bench()

        .title("Product of array except self")
        .relative(true)

        .run(
            NAMEOF_RAW(base::product_except_self<Itr, Itr>).c_str(),
            [&actual]() {
                forfun::product_except_self::base::product_except_self(
                    nums.cbegin(), nums.cend(), actual.begin(), actual.end());
                ankerl::nanobench::doNotOptimizeAway(actual);
            })

        .run(
            NAMEOF_RAW(fast::product_except_self<Itr, Itr>).c_str(),
            [&actual]() {
                forfun::product_except_self::fast::product_except_self(
                    nums.cbegin(), nums.cend(), actual.begin(), actual.end());
                ankerl::nanobench::doNotOptimizeAway(actual);
            })

        ;
}
