// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/search/koko_eating_bananas.hpp"

TEST_CASE("Koko eating bananas", "[koko_eating_bananas]")
{
    using forfun::search::koko_eating_bananas::min_eating_speed;

    SECTION("Two piles")
    {
        static constexpr int const duration{3};
        static constexpr std::array const piles{83, 89};

        static constexpr int const expected{83};

        STATIC_REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }
}
