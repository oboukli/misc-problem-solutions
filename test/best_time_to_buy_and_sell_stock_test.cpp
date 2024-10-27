// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/best_time_to_buy_and_sell_stock.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Best time to buy and sell stock",
    "[best_time_to_buy_and_sell_stock]",
    (auto calc_max_profit, calc_max_profit),
    forfun::best_time_to_buy_and_sell_stock::calc_max_profit,
    forfun::best_time_to_buy_and_sell_stock::optimized_l1::calc_max_profit,
    forfun::best_time_to_buy_and_sell_stock::optimized_l2::calc_max_profit
)
{
    SECTION("Empty price container")
    {
        std::array<int, 0U> const prices{};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("One price")
    {
        std::array const prices{19};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("Two prices where profit is possible")
    {
        std::array const prices{7, 19};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 12);
    }

    SECTION("Two prices where profit is impossible")
    {
        std::array const prices{19, 7};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("Three prices where profit is possible - case 1")
    {
        std::array const prices{5, 7, 19};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 14);
    }

    SECTION("Three prices where profit is possible - case 2")
    {
        std::array const prices{7, 5, 19};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 14);
    }

    SECTION("Three prices where profit is impossible")
    {
        std::array const prices{19, 7, 3};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("Thirty-two prices where profit is possible (benchmark case)")
    {
        std::array const prices{
            2,   5,   11,  17,  23,  29,  41,  47,  53,  59,  71,
            83,  89,  101, 107, 113, 131, 137, 149, 167, 173, 179,
            191, 197, 227, 233, 239, 251, 257, 263, 269, 271,
        };

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 269);
    }

    SECTION("Thirty-two prices where profit is impossible")
    {
        std::array const prices{
            271, 269, 263, 257, 251, 239, 233, 227, 197, 191, 179,
            173, 167, 149, 137, 131, 113, 107, 101, 89,  83,  71,
            59,  53,  47,  41,  29,  23,  17,  11,  5,   2,
        };

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("LeetCode test case 1")
    {
        std::array const prices{7, 1, 5, 3, 6, 4};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 5);
    }

    SECTION("LeetCode test case 2")
    {
        std::array const prices{7, 6, 4, 3, 1};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("NeetCode test case 1")
    {
        std::array const prices{10, 1, 5, 6, 7, 1};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 6);
    }

    SECTION("NeetCode test case 2")
    {
        std::array const prices{10, 8, 7, 5, 2};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("GeeksforGeeks test case 1")
    {
        std::array const prices{7, 10, 1, 3, 6, 9, 2};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 8);
    }

    SECTION("GeeksforGeeks test case 2")
    {
        std::array const prices{7, 6, 4, 3, 1};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 0);
    }

    SECTION("GeeksforGeeks test case 3")
    {
        std::array const prices{1, 3, 6, 9, 11};

        CAPTURE(prices);

        REQUIRE(calc_max_profit(prices) == 10);
    }
}
