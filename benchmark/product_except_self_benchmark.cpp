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
    "Product of array except self benchmarking",
    "[benchmark][product_except_self]"
)
{
    using namespace forfun::product_except_self;

    static constexpr std::array<std::uint64_t, 16> const input{
        1U,
        2U,
        3U,
        4U,
        5U,
        6U,
        7U,
        8U,
        9U,
        10U,
        11U,
        12U,
        13U,
        14U,
        15U,
        0U,
    };

    using ConstItr = decltype(input)::const_iterator;
    using Iter = std::remove_const_t<decltype(input)>::iterator;

    ankerl::nanobench::Bench()

        .title("Product of array except self")
        .relative(true)

        .run(
            NAMEOF_RAW(
                alg1::product_except_self<ConstItr, ConstItr, Iter, Iter>
            )
                .c_str(),
            [] noexcept -> void {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<std::uint64_t, 16> result /*[[indeterminate]]*/;
                forfun::product_except_self::alg1::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end()
                );

                ankerl::nanobench::doNotOptimizeAway(result);
            }
        )
        .run(
            NAMEOF_RAW(
                alg2::product_except_self<ConstItr, ConstItr, Iter, Iter>
            )
                .c_str(),
            [] noexcept -> void {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<std::uint64_t, 16> result /*[[indeterminate]]*/;
                forfun::product_except_self::alg2::product_except_self(
                    input.cbegin(), input.cend(), result.begin(), result.end()
                );

                ankerl::nanobench::doNotOptimizeAway(result);
            }
        )

        ;
}
