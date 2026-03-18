// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/array_concatenation.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Concatenate empty array",
    "[array_concatenation]",
    (auto concatenate, concatenate),
    (forfun::array_concatenation::functional::concatenate<int, 0>),
    (forfun::array_concatenation::iterator_based::concatenate<int, 0>),
    (forfun::array_concatenation::iterator_based_double::concatenate<int, 0>),
    (forfun::array_concatenation::iterator_unfolded::concatenate<int, 0>),
    (forfun::array_concatenation::nested_loops::concatenate<int, 0>),
    (forfun::array_concatenation::semi_unfolded::concatenate<int, 0>)
)
{
    static constexpr std::array<int, 0> const src{};
    static constexpr std::array<int, 0> const expected{};
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    std::array<int, 0> dest /*[[indeterminate]]*/;

    concatenate(src, dest);

    STATIC_REQUIRE(dest == expected);
}
