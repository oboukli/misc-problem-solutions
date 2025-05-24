// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/majority_element.hpp"

TEST_CASE("Majority element", "[majority_element]")
{
    using forfun::majority_element::majority_element;

    SECTION("Empty collection should have no majority")
    {
        constexpr std::array<int, 0> const elements{};

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("One-element collection should have no majority")
    {
        constexpr std::array const elements{7};

        static_assert(elements.size() == 1UZ);

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("A collection of two unique elements should have no majority")
    {
        constexpr std::array const elements{5, 7};

        static_assert(elements.size() == 2UZ);

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("A collection of three unique elements should have no majority")
    {
        constexpr std::array const elements{3, 5, 7};

        static_assert(elements.size() == 3UZ);

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }
}
