// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <limits>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/hamming_weight.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Humming weight",
    "[hamming_weight]",
    (auto get_hamming_weight, get_hamming_weight),
    forfun::hamming_weight::linear_functional::get_hamming_weight,
    forfun::hamming_weight::linear_imperative::get_hamming_weight,
    forfun::hamming_weight::optimized_imperative::get_hamming_weight
)
{
    SECTION("Zero")
    {
        REQUIRE(get_hamming_weight(0) == 0UZ);
    }

    SECTION("One")
    {
        REQUIRE(get_hamming_weight(1) == 1UZ);
    }

    SECTION("Eighty-five in decimal has four ones in binary")
    {
        static constexpr std::size_t const n{0b01010101};
        static_assert(n == 85UZ);

        REQUIRE(get_hamming_weight(n) == 4UZ);
    }

    SECTION("Eleven in decimal has three ones in binary")
    {
        REQUIRE(get_hamming_weight(11) == 3UZ);
    }

    SECTION("Two hundred fifty-six in decimal has one one in binary")
    {
        REQUIRE(get_hamming_weight(256) == 1UZ);
    }

    SECTION("Max std::size_t value")
    {
        REQUIRE(
            get_hamming_weight(std::numeric_limits<std::size_t>::max())
            == std::numeric_limits<std::size_t>::digits
        );
    }

    SECTION("Only the most and least significant bits are set (benchmark case)")
    {
        static constexpr std::size_t const n{
            (1UZ << std::size_t{std::numeric_limits<std::size_t>::digits - 1})
            | 1UZ
        };

        REQUIRE(get_hamming_weight(n) == 2UZ);
    }

    SECTION("LeetCode case")
    {
        REQUIRE(get_hamming_weight(2147483645) == 30UZ);
    }
}
