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
        unsigned int const volatile test_input{0U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1 (static)")
    {
        static constexpr unsigned int const actual{find_sum_mult_three_five(1U)
        };

        STATIC_REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 4 (static)")
    {
        static constexpr unsigned int const actual{find_sum_mult_three_five(3U)
        };

        STATIC_REQUIRE(actual == 0U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 4 (static)")
    {
        static constexpr unsigned int const actual{find_sum_mult_three_five(4U)
        };

        STATIC_REQUIRE(actual == 3U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 6 (static)")
    {
        static constexpr unsigned int const actual{find_sum_mult_three_five(6U)
        };

        STATIC_REQUIRE(actual == 8U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 10 (static)")
    {
        static constexpr unsigned int const actual{find_sum_mult_three_five(10U)
        };

        STATIC_REQUIRE(actual == 23U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 11")
    {
        unsigned int const volatile test_input{11U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 33U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 100")
    {
        unsigned int const volatile test_input{100U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 2'318U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1000 (static)")
    {
        static_assert(sizeof(unsigned int) >= 4U);

        static constexpr unsigned int const actual{
            find_sum_mult_three_five(1'000U)
        };

        STATIC_REQUIRE(actual == 233'168U);
    }

    SECTION("Find the sum of all the multiples of 3 or 5 below 1000")
    {
        static_assert(sizeof(unsigned int) >= 4U);

        unsigned int const volatile test_input{1'000U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 233'168U);
    }

    SECTION(
        "Find the sum of all the multiples of 3 or 5 below max unsigned 32-bit "
        "safe limit"
    )
    {
        static_assert(sizeof(unsigned int) >= 4U);

        unsigned int const volatile test_input{89'739U};
        CAPTURE(test_input);

        unsigned int const actual{find_sum_mult_three_five(test_input)};

        REQUIRE(actual == 1'878'991'079U);
    }
}
