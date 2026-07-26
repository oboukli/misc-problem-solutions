// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/product_except_self.hpp"

namespace {

using IntArr3ConstIter = std::array<int, 3>::const_iterator;
using IntArr3Iter = std::array<int, 3>::iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::array<int, 3>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        IntArr3ConstIter,
        IntArr3ConstIter,
        IntArr3Iter,
        IntArr3Iter>),
    (forfun::product_except_self::alg2::product_except_self<
        IntArr3ConstIter,
        IntArr3ConstIter,
        IntArr3Iter,
        IntArr3Iter>)
)
{
    SECTION("Input is of three integers")
    {
        static constexpr auto actual{
            [] [[nodiscard]] consteval noexcept -> std::array<int, 3> {
                static constexpr std::array const nums{0, 1, 1};

                std::array<int, 3> result{};

                product_except_self(
                    nums.cbegin(), nums.cend(), result.begin(), result.end()
                );

                return result;
            }()
        };

        static constexpr std::array const expected{1, 0, 0};

        STATIC_REQUIRE(actual == expected);
    }
}
