// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/trapping_rainwater.hpp"

TEST_CASE("Trapping Rainwater", "[trapping_rainwater]")
{
    using forfun::trapping_rainwater::trap;

    SECTION("One elevation")
    {
        static constexpr std::array<int, 1> const elevations{19};

        STATIC_REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Three elevations, capacity is 4")
    {
        static constexpr std::array const elevations{5, 0, 4};

        STATIC_REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 4);
    }
}
