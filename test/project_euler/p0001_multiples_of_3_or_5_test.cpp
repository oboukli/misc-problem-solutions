// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"

TEST_CASE("Multiples of three or five", "[multiples_of_3_or_5]")
{
    using forfun::project_euler::multiples_of_3_or_5::find_sum_mult_three_five;

    SECTION("Find the sum of all the multiples of 3 or 5 below 0")
    {
        int const volatile test_input{0};
        CAPTURE(test_input);

        int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 0);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(1)};

        STATIC_REQUIRE(actual == 0);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 4 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(3)};

        STATIC_REQUIRE(actual == 0);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 4 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(4)};

        STATIC_REQUIRE(actual == 3);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 6 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(6)};

        STATIC_REQUIRE(actual == 8);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 10 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(10)};

        STATIC_REQUIRE(actual == 23);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 11")
    {
        int const volatile test_input{11};
        CAPTURE(test_input);

        int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 33);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 100")
    {
        int const volatile test_input{100};
        CAPTURE(test_input);

        int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 2'318);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1000 (static)")
    {
        static constexpr int const actual{find_sum_mult_three_five(1'000)};

        STATIC_REQUIRE(actual == 233'168);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1000")
    {
        int const volatile test_input{1'000};
        CAPTURE(test_input);

        int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 233'168);
    }
}
