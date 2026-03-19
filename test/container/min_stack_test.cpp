// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/container/min_stack.hpp"

TEMPLATE_TEST_CASE(
    "Min cache",
    "[min_stack]",
    forfun::container::min_stack::cache_friendly::min_stack,
    forfun::container::min_stack::double_buffered::min_stack
)
{
    using StackType = TestType;

    SECTION("Default constructed stack's size is initially zero")
    {
        StackType const stack;

        REQUIRE(stack.size() == 0UZ);
    }

    SECTION("Default constructed stack is initially empty")
    {
        StackType const stack;

        REQUIRE(stack.empty());
    }

    SECTION("Default initialed stack size is initially zero")
    {
        StackType const stack{};

        REQUIRE(stack.size() == 0UZ);
    }

    SECTION("Default initialed stack is initially empty")
    {
        StackType const stack{};

        REQUIRE(stack.empty());
    }

    SECTION("Stack is not empty after push")
    {
        StackType stack{};

        stack.push(11447);

        REQUIRE_FALSE(stack.empty());

        stack.push(11467);

        REQUIRE_FALSE(stack.empty());
    }

    SECTION("Stack size increases after push")
    {
        StackType stack{};

        stack.push(11471);

        REQUIRE(stack.size() == 1UZ);

        stack.push(11483);

        REQUIRE(stack.size() == 2UZ);

        stack.push(-3);

        REQUIRE(stack.size() == 3UZ);

        stack.push(11489);

        REQUIRE(stack.size() == 4UZ);
    }

    SECTION("Stack is empty when all elements are popped")
    {
        StackType stack{};

        stack.push(11491);
        stack.push(11497);

        stack.pop();
        stack.pop();

        REQUIRE(stack.empty());
    }

    SECTION("Stack size decrease after pop")
    {
        StackType stack{};

        stack.push(11503);
        stack.push(11519);

        stack.pop();

        REQUIRE(stack.size() == 1UZ);

        stack.pop();

        REQUIRE(stack.size() == 0UZ);
    }

    SECTION("Stack top changes after push")
    {
        StackType stack{};

        stack.push(-11579);

        REQUIRE(stack.top() == -11579);

        stack.push(0);

        REQUIRE(stack.top() == 0);
    }

    SECTION("Stack min changes after push")
    {
        StackType stack{};

        stack.push(-32);
        stack.push(100);

        REQUIRE(stack.min() == -32);

        stack.push(-33);

        REQUIRE(stack.min() == -33);
    }

    SECTION("Stack top changes after pop")
    {
        StackType stack{};

        stack.push(11527);
        stack.push(11549);

        stack.pop();

        REQUIRE(stack.top() == 11527);
    }

    SECTION("Stack min changes after pop")
    {
        StackType stack{};

        stack.push(11593);
        stack.push(11587);

        stack.pop();

        REQUIRE(stack.min() == 11593);
    }

    SECTION("Benchmark case")
    {
        StackType stack{};

        stack.push(16);
        stack.push(15);
        stack.push(14);
        stack.push(13);

        CHECK(stack.min() == 13);
        CHECK(stack.top() == 13);
        CHECK(stack.size() == 4);

        stack.push(-9);
        stack.push(-9);
        stack.push(-9);
        stack.push(-9);

        stack.pop();

        CHECK(stack.min() == -9);
        CHECK(stack.top() == -9);
        CHECK(stack.size() == 7);

        stack.push(8);
        stack.push(7);
        stack.push(6);
        stack.push(5);

        stack.push(4);
        stack.push(3);
        stack.push(2);
        stack.push(1);

        CHECK(stack.min() == -9);
        CHECK(stack.top() == 1);
        CHECK(stack.size() == 15);

        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();

        CHECK(stack.min() == -9);
        CHECK(stack.top() == 5);
        CHECK(stack.size() == 11);

        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();

        CHECK(stack.min() == -9);
        CHECK(stack.top() == -9);
        CHECK(stack.size() == 7);

        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();

        CHECK(stack.min() == 14);
        CHECK(stack.top() == 14);

        stack.pop();
        stack.pop();
        stack.pop();

        REQUIRE(stack.empty());
    }

    SECTION("LeetCode case")
    {
        StackType stack{};

        stack.push(-2);
        stack.push(0);
        stack.push(-3);

        REQUIRE(stack.min() == -3);

        stack.pop();

        REQUIRE(stack.top() == 0);

        REQUIRE(stack.min() == -2);
    }

    SECTION("NeetCode case")
    {
        StackType stack{};

        stack.push(1);
        stack.push(2);
        stack.push(0);

        REQUIRE(stack.min() == 0);

        stack.pop();

        REQUIRE(stack.top() == 2);

        REQUIRE(stack.min() == 1);
    }
}

// References:
// https://leetcode.com/problems/min-stack/
// https://neetcode.io/problems/minimum-stack/
