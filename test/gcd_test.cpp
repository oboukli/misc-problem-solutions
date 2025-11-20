// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/gcd.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (zero argument)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of 0 and 0 is 0")
    {
        REQUIRE(gcd(0, 0) == 0);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (zero and positive argument)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of 0 and 1 is 1")
    {
        REQUIRE(gcd(0, 1) == 1);
        REQUIRE(gcd(1, 0) == 1);
    }

    SECTION("The GCD of 0 and 6 is 6")
    {
        REQUIRE(gcd(0, 6) == 6);
        REQUIRE(gcd(6, 0) == 6);
    }

    SECTION("The GCD of 0 and 17 is 17")
    {
        REQUIRE(gcd(0, 17) == 17);
        REQUIRE(gcd(17, 0) == 17);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (zero and negative argument)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of 0 and -1 is 1")
    {
        REQUIRE(gcd(-1, 0) == 1);
        REQUIRE(gcd(0, -1) == 1);
    }

    SECTION("The GCD of 0 and -4 is 4")
    {
        REQUIRE(gcd(-4, 0) == 4);
        REQUIRE(gcd(0, -4) == 4);
    }

    SECTION("The GCD of 0 and -9 is 9")
    {
        REQUIRE(gcd(-9, 0) == 9);
        REQUIRE(gcd(0, -9) == 9);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (positive non-zero argument)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of 1 and 1 is 1")
    {
        REQUIRE(gcd(1, 1) == 1);
        REQUIRE(gcd(1, 1) == 1);
    }

    SECTION("The GCD of 2 and 3 is 1")
    {
        REQUIRE(gcd(2, 3) == 1);
        REQUIRE(gcd(3, 2) == 1);
    }

    SECTION("The GCD of 60 and 24 is 12")
    {
        REQUIRE(gcd(60, 24) == 12);
        REQUIRE(gcd(24, 60) == 12);
    }

    SECTION("The GCD of 252 and 105 is 21")
    {
        REQUIRE(gcd(252, 105) == 21);
        REQUIRE(gcd(105, 252) == 21);
    }

    SECTION(
        "The GCD of 1,934,917,632 and 33,554,432 is 32,768 (benchmark case)"
    )
    {
        REQUIRE(gcd(1'934'917'632, 33'554'432) == 32'768);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (negative non-zero argument)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of -252 and -105 is 21")
    {
        REQUIRE(gcd(-252, -105) == 21);
        REQUIRE(gcd(-105, -252) == 21);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Greatest common divisor (mixed negative and positive non-zero arguments)",
    "[gcd]",
    (auto gcd, gcd),
    forfun::gcd::euclid::recursive::gcd
)
{
    SECTION("The GCD of 1 and -1 is 1")
    {
        REQUIRE(gcd(1, -1) == 1);
        REQUIRE(gcd(-1, 1) == 1);
    }

    SECTION("The GCD of 252 and -105 is 21")
    {
        REQUIRE(gcd(252, -105) == 21);
        REQUIRE(gcd(-105, 252) == 21);
    }
}
