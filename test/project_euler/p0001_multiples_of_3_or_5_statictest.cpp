// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"

TEST_CASE("Multiples of three or five", "[multiples_of_3_or_5]")
{
    using forfun::project_euler::multiples_of_3_or_5::find_sum_mult_three_five;

    SECTION("Find the sum of all the multiples of 3 or 5 up to 0")
    {
        static constexpr unsigned int const test_input{0U};

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        STATIC_REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 1")
    {
        static constexpr unsigned int const actual{
            find_sum_mult_three_five(1U)
        };

        STATIC_REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 3")
    {
        static constexpr unsigned int const actual{
            find_sum_mult_three_five(3U)
        };

        STATIC_REQUIRE(actual == 3U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 10")
    {
        static constexpr unsigned int const actual{
            find_sum_mult_three_five(10U)
        };

        STATIC_REQUIRE(actual == 33U);
    }
}
