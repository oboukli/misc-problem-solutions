// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/bubble_sort.hpp"

namespace {

using Arr0Iter = std::array<int, 0>::iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 0>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr0Iter, Arr0Iter>),
    (forfun::sorting::stl::bubble_sort<Arr0Iter, Arr0Iter>)
)
{
    SECTION("Empty container")
    {
        static constexpr std::array<int, 0> const expected_output{};

        std::array<int, 0> test_input{};

        bubble_sort(test_input.begin(), test_input.end());

        STATIC_CHECK(test_input.empty());

        STATIC_REQUIRE(test_input == expected_output);
    }
}
