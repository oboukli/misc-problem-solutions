// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/fibonacci.hpp"

TEST_CASE("Find Fibonacci number", "[fibonacci]")
{
    using forfun::fibonacci::recursive::fib;

    SECTION("Negative value case (n = -1)")
    {
        constexpr auto const n{-1};

        CAPTURE(n);

        STATIC_REQUIRE(fib(n) == 0);
    }

    SECTION("First (zeroth) Fibonacci number (n = 0) is zero")
    {
        constexpr auto const n{0};

        CAPTURE(n);

        STATIC_REQUIRE(fib(n) == 0);
    }

    SECTION("Second Fibonacci number (n = 1) is one")
    {
        constexpr auto const n{1};

        CAPTURE(n);

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
