// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/product_except_self.hpp"

inline constexpr std::array const input{
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,
    4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
    13, 14, 15, 16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 1,  2,
    3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
};
static_assert(input.size() == decltype(input)::size_type{128});

TEST_CASE(
    "product_except_self benchmarking", "[benchmark][product_except_self]")
{
    using namespace forfun::product_except_self;

    std::remove_const_t<decltype(input)> result{};

    using CnstItr = decltype(input)::const_iterator;
    using Itr = decltype(result)::iterator;

    ankerl::nanobench::Bench()

        .title("Product of array except self")
        .relative(true)

        .run(
            NAMEOF_RAW(base::product_except_self<CnstItr, Itr>).c_str(),
            [&result]() {
                forfun::product_except_self::base::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end());

                ankerl::nanobench::doNotOptimizeAway(result);
            })

        .run(
            NAMEOF_RAW(fast::product_except_self<CnstItr, Itr>).c_str(),
            [&result]() {
                forfun::product_except_self::fast::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end());

                ankerl::nanobench::doNotOptimizeAway(result);
            })

        ;
}
