// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/last_stone_weight.hpp"

using Iter = std::vector<int>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Last stone weight (iterator-based strategies)",
    "[last_stone_weight]",
    (auto last_stone_weight, last_stone_weight),
    (forfun::last_stone_weight::naive::last_stone_weight<Iter, Iter>),
    (forfun::last_stone_weight::partially_sorted::last_stone_weight<Iter, Iter>)
)
{
    SECTION("One element; Element is positive non-zero")
    {
        std::vector stones{17};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 17);
    }

    SECTION("Two ones")
    {
        std::vector stones{1, 1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three ones")
    {
        std::vector stones{1, 1, 1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("Two equal elements")
    {
        std::vector stones{19, 19};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three equal elements")
    {
        std::vector stones{13, 13, 13};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 13);
    }

    SECTION("Four equal elements")
    {
        std::vector stones{17, 17, 17, 17};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Two non-equal elements")
    {
        std::vector stones{2, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 5);
    }

    SECTION("Three non-equal elements evaluating to zero")
    {
        std::vector stones{5, 2, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three non-equal elements evaluating to non-zero")
    {
        std::vector stones{8, 5, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 4);
    }

    SECTION("Four arbitrary elements evaluating to zero")
    {
        std::vector stones{4, 10, 5, 9};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Four arbitrary elements evaluating to non-zero")
    {
        std::vector stones{2, 4, 7, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("Five arbitrary elements evaluating to zero")
    {
        std::vector stones{2, 4, 7, 3, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Five arbitrary elements evaluating to non-zero")
    {
        std::vector stones{4, 5, 7, 5, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 3);
    }
}
