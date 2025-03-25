// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/insertion_sort.hpp"

TEST_CASE("Insertion sort", "[sorting][insertion_sort]")
{
    using forfun::sorting::insertion_sort;

    SECTION("Empty container")
    {
        std::array<int, 0U> test_input{};
        static constexpr std::array<int, 0U> const expected_output{};
        insertion_sort(test_input.begin(), test_input.end());

        STATIC_CHECK(test_input.empty());

        STATIC_REQUIRE(test_input == expected_output);
    }
}
