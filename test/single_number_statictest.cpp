// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <limits>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/single_number.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Single number",
    "[single_number]",
    (auto get_single, get_single),
    (forfun::single_number::functional::get_single<std::array<int, 5> const&>),
    (forfun::single_number::imperative::get_single<std::array<int, 5> const&>)
)
{
    SECTION("Limits of int")
    {
        // https://en.wikipedia.org/wiki/Delicate_prime
        static constexpr int const delicate_prime{4393139};

        static constexpr std::array const nums{
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
            delicate_prime,
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
        };

        STATIC_REQUIRE(get_single(nums) == delicate_prime);
    }
}
