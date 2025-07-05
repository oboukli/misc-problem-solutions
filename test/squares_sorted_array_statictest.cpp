// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/squares_sorted_array.hpp"

namespace {

using ConstIter = std::array<int, 0>::const_iterator;
using Iter = std::array<int, 0>::iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Squares of a sorted array",
    "[squares_sorted_array]",
    (auto squares_sorted, squares_sorted),
    (forfun::squares_sorted_array::squares_sorted<ConstIter, Iter>),
    (forfun::squares_sorted_array::squares_sorted_special<ConstIter, Iter>)
)
{
    SECTION("Empty")
    {
        static constexpr std::array<int, 0> expected{};

        static constexpr std::array<int, 0> const input{};
        std::array<int, 0> result_squares{};

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        STATIC_REQUIRE(result_squares == expected);
    }
}

TEST_CASE("Squares of a sorted array (unsigned)", "[squares_sorted_array]")
{
    using forfun::squares_sorted_array::squares_sorted;

    SECTION("Empty")
    {
        static constexpr std::array<unsigned int, 0> expected{};

        static constexpr std::array<unsigned int, 0> const input{};
        std::array<unsigned int, 0> result_squares{};

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        STATIC_REQUIRE(result_squares == expected);
    }
}
