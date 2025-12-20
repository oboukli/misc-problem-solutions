// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/quicksort.hpp"

TEST_CASE("Quicksort sort", "[sorting][quicksort]")
{
    using forfun::sorting::quicksort;

    SECTION("Empty container")
    {
        static constexpr std::array<int, 0> const expected_output{};

        std::array<int, 0> test_input{};

        quicksort(test_input.begin(), test_input.end());

        STATIC_CHECK(test_input.empty());

        STATIC_REQUIRE(test_input == expected_output);
    }
}
