// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/missing_number.hpp"

namespace {

using Range = std::array<int, 10>;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Missing number",
    "[missing_number]",
    (auto find_missing_number, find_missing_number),
    forfun::missing_number::bitwise::find_missing_number<Range const&>,
    forfun::missing_number::functional::find_missing_number<Range const&>,
    forfun::missing_number::imperative::find_missing_number<Range const&>
)
{
    SECTION("Ten numbers")
    {
        static constexpr std::array const nums{4, 3, 9, 10, 1, 2, 7, 5, 6, 0};

        STATIC_REQUIRE(find_missing_number(nums) == 8);
    }
}
