// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <forward_list>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/add_two_numbers.hpp"

TEST_CASE("Add two numbers", "[add_two_numbers]")
{
    using forfun::add_two_numbers::stl::add_two_numbers;

    SECTION("0 + 0")
    {
        std::forward_list const addend_a{0U};

        std::forward_list const addend_b{0U};

        std::forward_list const expected{0U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("0 + 1")
    {
        std::forward_list const addend_a{0U};

        std::forward_list const addend_b{1U};

        std::forward_list const expected{1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("1 + 0")
    {
        std::forward_list const addend_a{1U};

        std::forward_list const addend_b{0U};

        std::forward_list expected{1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("1 + 1")
    {
        std::forward_list const addend_a{1U};

        std::forward_list const addend_b{1U};

        std::forward_list const expected{2U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("3 + 7")
    {
        std::forward_list const addend_a{3U};

        std::forward_list const addend_b{7U};

        std::forward_list const expected{0U, 1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("1 + 10")
    {
        std::forward_list const addend_a{1U};

        std::forward_list const addend_b{0U, 1U};

        std::forward_list const expected{1U, 1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("100 + 100")
    {
        std::forward_list const addend_a{0U, 0U, 1U};

        std::forward_list const addend_b{0U, 0U, 1U};

        std::forward_list const expected{0U, 0U, 2U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("100 + 910")
    {
        std::forward_list const addend_a{0U, 0U, 1U};

        std::forward_list const addend_b{0U, 1U, 9U};

        std::forward_list const expected{0U, 1U, 0U, 1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("342 + 465 = 807 (LeetCode test case)")
    {
        std::forward_list const addend_a{2U, 4U, 3U};

        std::forward_list const addend_b{5U, 6U, 4U};

        std::forward_list const expected{7U, 0U, 8U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("9999999 + 9999 = 10009998 (LeetCode test case)")
    {
        std::forward_list const addend_a{9U, 9U, 9U, 9U, 9U, 9U, 9U};

        std::forward_list const addend_b{9U, 9U, 9U, 9U};

        std::forward_list const expected{8U, 9U, 9U, 9U, 0U, 0U, 0U, 1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }

    SECTION("256541 + 997991 = 1254532 (benchmark case)")
    {
        std::forward_list const addend_a{1U, 4U, 5U, 6U, 5U, 2U};

        std::forward_list const addend_b{1U, 9U, 9U, 7U, 9U, 9U};

        std::forward_list const expected{2U, 3U, 5U, 4U, 5U, 2U, 1U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }
}

TEST_CASE("Add two numbers (degenerate case)", "[add_two_numbers]")
{
    using forfun::add_two_numbers::stl::add_two_numbers;

    SECTION("Empty lists")
    {
        std::forward_list<unsigned> const addend_a{};

        std::forward_list<unsigned> const addend_b{};

        std::forward_list const expected{0U};

        CAPTURE(addend_a);
        CAPTURE(addend_b);
        REQUIRE(add_two_numbers(addend_a, addend_b) == expected);
    }
}
