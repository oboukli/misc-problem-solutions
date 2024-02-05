// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstdint>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/product_except_self.hpp"

TEST_CASE(
    "product_except_self benchmarking", "[benchmark][product_except_self]")
{
    using namespace forfun::product_except_self;

    static constexpr std::array<std::uint64_t, 16> const input{
        // clang-format off
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
        // clang-format on
    };

    using CnstItr = decltype(input)::const_iterator;
    using Itr = std::remove_const_t<decltype(input)>::iterator;

    ankerl::nanobench::Bench()

        .title("Product of array except self")
        .relative(true)

        .run(
            NAMEOF_RAW(alg1::product_except_self<CnstItr, Itr>).c_str(),
            []() {
                std::array<std::uint64_t, 16> result;
                forfun::product_except_self::alg1::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end());

                ankerl::nanobench::doNotOptimizeAway(result);
            })
        .run(
            NAMEOF_RAW(alg2::product_except_self<CnstItr, Itr>).c_str(),
            []() {
                std::array<std::uint64_t, 16> result;
                forfun::product_except_self::alg2::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end());

                ankerl::nanobench::doNotOptimizeAway(result);
            })

        ;
}
