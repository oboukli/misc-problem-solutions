// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/gcd.hpp"

TEST_CASE("Greatest common divisor", "[gcd]")
{
    using forfun::gcd::euclid::recursive::gcd;

    SECTION("The GCD of 0 and 0 is 0")
    {
        REQUIRE(gcd(0, 0) == 0);
    }

    SECTION("The GCD of 1 and 0 is 1")
    {
        REQUIRE(gcd(-1, 0) == 1);
        REQUIRE(gcd(0, -1) == 1);
    }

    SECTION("The GCD of 0 and 17 is 17")
    {
        REQUIRE(gcd(0, 17) == 17);
        REQUIRE(gcd(17, 0) == 17);
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

    SECTION("The GCD of 252 and 105 is 21")
    {
        REQUIRE(gcd(-252, -105) == 21);
        REQUIRE(gcd(-105, -252) == 21);
    }

    SECTION(
        "The GCD of 1,934,917,632 and 33,554,432 is 32,768 (benchmark case)")
    {
        REQUIRE(gcd(1'934'917'632, 33'554'432) == 32'768);
    }
}
