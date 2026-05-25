// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/minimum_rotated_element.hpp"

namespace {

using CIter1 = std::array<int, 1>::const_iterator;

using CIter4 = std::array<int, 4>::const_iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Find minimum in rotated sorted array (one element case)",
    "[minimum_rotated_element]",
    (auto find_min, find_min),
    // clang-format off
    (forfun::search::minimum_rotated_element::iterative::
        find_min<CIter1, CIter1>),
    (forfun::search::minimum_rotated_element::recursive::
        find_min<CIter1, CIter1>)
    // clang-format on
)
{
    static constexpr std::array<int, 1> const elements{19};

    static constexpr auto const result{
        find_min(elements.cbegin(), elements.cend())
    };

    STATIC_REQUIRE_FALSE(result == elements.cend());

    STATIC_REQUIRE(*result == 19);

    STATIC_REQUIRE(result == std::ranges::min_element(elements));
}

TEMPLATE_TEST_CASE_SIG(
    "Find minimum in rotated sorted array (four elements case)",
    "[minimum_rotated_element]",
    (auto find_min, find_min),
    // clang-format off
    (forfun::search::minimum_rotated_element::iterative::
        find_min<CIter4, CIter4>),
    (forfun::search::minimum_rotated_element::recursive::
        find_min<CIter4, CIter4>)
    // clang-format on
)
{
    static constexpr std::array const elements{7001, 7013, 7019, 7027};

    static constexpr auto const result{
        find_min(elements.cbegin(), elements.cend())
    };

    STATIC_REQUIRE_FALSE(result == elements.cend());

    STATIC_REQUIRE(*result == 7001);

    STATIC_REQUIRE(result == std::ranges::min_element(elements));
}
