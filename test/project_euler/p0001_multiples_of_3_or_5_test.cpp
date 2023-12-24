// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"

TEST_CASE("find_sum_mult_three_five", "[multiples_of_3_or_5]")
{
    using forfun::project_euler::multiples_of_3_or_5::find_sum_mult_three_five;

    SECTION("Static test 01")
    {
        static constexpr int const s{find_sum_mult_three_five(1)};
        STATIC_REQUIRE(s == 0);
    }

    SECTION("Static test 02")
    {
        static constexpr int const s{find_sum_mult_three_five(4)};
        STATIC_REQUIRE(s == 3);
    }

    SECTION("Static test 03")
    {
        static constexpr int const s{find_sum_mult_three_five(6)};
        STATIC_REQUIRE(s == 8);
    }

    SECTION("Static test 04")
    {
        static constexpr int const s{find_sum_mult_three_five(10)};
        STATIC_REQUIRE(s == 23);
    }

    SECTION("Static test 05")
    {
        static constexpr int const s{find_sum_mult_three_five(11)};
        STATIC_REQUIRE(s == 33);
    }

    SECTION("Static test 06")
    {
        static constexpr int const s{find_sum_mult_three_five(1000)};
        STATIC_REQUIRE(s == 233168);
    }

    SECTION("Runtime test")
    {
        int volatile test_input{1000};
        int const actual{find_sum_mult_three_five(test_input)};
        REQUIRE(actual == 233168);
    }
}
