// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/fibonacci.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Find Fibonacci number",
    "[fibonacci]",
    ((auto fib), fib),
    (forfun::fibonacci::iterative::fib<int>),
    (forfun::fibonacci::recursive::fib<int>))
{
    SECTION("Negative value case (n = -1)")
    {
        static constexpr int const n{-1};

        STATIC_REQUIRE(fib(n) == 0);
    }

    SECTION("First (zeroth) Fibonacci number (n = 0) is zero")
    {
        static constexpr int const n{0};

        STATIC_REQUIRE(fib(n) == 0);
    }

    SECTION("Second Fibonacci number (n = 1) is one")
    {
        static constexpr int const n{1};

        STATIC_REQUIRE(fib(n) == 1);
    }

    SECTION("Third Fibonacci number (n = 2) is one")
    {
        auto const volatile n{2};

        CAPTURE(n);

        REQUIRE(fib(n) == 1);
    }

    SECTION("Eighth Fibonacci number is (n = 7) thirteen")
    {
        auto const volatile n{7};

        CAPTURE(n);

        REQUIRE(fib(n) == 13);
    }
}
