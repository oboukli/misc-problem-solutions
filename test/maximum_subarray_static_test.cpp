// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/maximum_subarray.hpp"

TEST_CASE("Maximum subarray constexpr tests", "[maximum_subarray]")
{
    SECTION("Static brute_force::max_sum(...)")
    {
        constexpr std::array const input{0};

        STATIC_REQUIRE(
            forfun::maximum_subarray::brute_force::max_sum(
                input.cbegin(), input.cend()
            )
            == 0
        );
    }

    SECTION("Static recursive::max_sum(...)")
    {
        constexpr std::array const input{0};

        STATIC_REQUIRE(
            forfun::maximum_subarray::recursive::max_sum(
                input.cbegin(), input.cend()
            )
            == 0
        );
    }

    SECTION("Static streaming::max_sum(...)")
    {
        constexpr std::array const input{0};

        STATIC_REQUIRE(
            forfun::maximum_subarray::streaming::max_sum(
                input.cbegin(), input.cend()
            )
            == 0
        );
    }
}
