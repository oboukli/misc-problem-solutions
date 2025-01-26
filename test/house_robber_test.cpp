// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/house_robber.hpp"

TEST_CASE("House robber", "[house_robber]")
{
    using forfun::house_robber::recursive::rob;

    SECTION("Empty container")
    {
        std::array<int, 0U> const stashes{};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == 0);
    }

    SECTION("One element")
    {
        std::array const stashes{5};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == 5);
    }

    SECTION("Two equal elements")
    {
        std::array const stashes{1, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == 1);
    }

    SECTION("Two elements")
    {
        std::array const stashes{37, 53};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == 53);
    }

    SECTION("Three equal elements")
    {
        std::array const stashes{1, 1, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (1 + 1));
    }

    SECTION("Three elements")
    {
        std::array const stashes{83, 41, 59};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (83 + 59));
    }

    SECTION("Four equal elements")
    {
        std::array const stashes{1, 1, 1, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (1 + 1));
    }

    SECTION("Four elements")
    {
        std::array const stashes{67, 79, 19, 89};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (79 + 89));
    }

    SECTION("Five elements where target value is four")
    {
        std::array const stashes{1, 3, 1, 0, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == 4);
    }

    SECTION("Six elements where target value is three")
    {
        std::array const stashes{1, 0, 1, 0, 1, 0};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (1 + 1 + 1));
    }

    SECTION("Seven elements where target value is four")
    {
        std::array const stashes{1, 0, 1, 0, 1, 0, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (1 + 1 + 1 + 1));
    }

    SECTION("Seven elements where target value is six")
    {
        std::array const stashes{1, 4, 1, 0, 1, 0, 1};

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == (4 + 1 + 1));
    }

    SECTION("First thirty-two primes (benchmark case)")
    {
        static constexpr int const expected{
            5
            + 17
            + 29
            + 47
            + 59
            + 83
            + 101
            + 113
            + 137
            + 167
            + 179
            + 197
            + 233
            + 251
            + 263
            + 271
        };
        static_assert(expected == 2152);

        std::array const stashes{
            2,   5,   11,  17,  23,  29,  41,  47,  53,  59,  71,
            83,  89,  101, 107, 113, 131, 137, 149, 167, 173, 179,
            191, 197, 227, 233, 239, 251, 257, 263, 269, 271,
        };

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == expected);
    }

    SECTION("First thirty-two primes in arbitrary order")
    {
        static constexpr int const expected{
            149
            + 179
            + 251
            + 197
            + 53
            + 233
            + 101
            + 257
            + 167
            + 113
            + 271
            + 173
            + 191
            + 263
        };
        static_assert(expected == 2598);

        std::array const stashes{
            149, 47,  179, 107, 11,  251, 71,  197, 137, 53,  59,
            233, 227, 101, 41,  257, 269, 167, 17,  5,   113, 239,
            271, 89,  29,  173, 23,  191, 2,   83,  263, 131,
        };

        CAPTURE(stashes);

        REQUIRE(rob(stashes.cbegin(), stashes.cend()) == expected);
    }
}
