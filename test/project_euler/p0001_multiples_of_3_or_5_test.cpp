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

    SECTION("Find the sum of all the multiples of 3 or 5 up to 0")
    {
        unsigned int const volatile test_input{};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 1")
    {
        unsigned int const volatile test_input{1U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 3")
    {
        unsigned int const volatile test_input{3U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 3U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 4")
    {
        unsigned int const volatile test_input{4U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 3U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 6")
    {
        unsigned int const volatile test_input{6U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 14U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 10")
    {
        unsigned int const volatile test_input{10U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 33U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 11")
    {
        unsigned int const volatile test_input{11};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 33U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 99")
    {
        unsigned int const volatile test_input{99};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 2'318U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 999")
    {
        unsigned int const volatile test_input{999U};
        CAPTURE(test_input);
        static_assert(sizeof(unsigned int) >= 4UZ);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 233'168U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 up to 999")
    {
        static_assert(sizeof(unsigned int) >= 4UZ);

        unsigned int const volatile test_input{999};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 233'168U);
    }

    SECTION(
        "Find the sum of all the multiples of 3 or 5 up to max unsigned 32-bit "
        "safe limit"
    )
    {
        static_assert(sizeof(unsigned int) >= 4UZ);

        unsigned int const volatile test_input{89'738};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 1'878'991'079U);
    }
}
