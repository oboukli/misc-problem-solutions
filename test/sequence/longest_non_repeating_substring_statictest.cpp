// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sequence/longest_non_repeating_substring.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Longest substring without repeating characters",
    "[longest_non_repeating_substring]",
    (auto longest_substring_length, longest_substring_length),
    forfun::longest_non_repeating_substring::index_based::
        longest_unique_substring_length,
    forfun::longest_non_repeating_substring::iterator_based::
        longest_unique_substring_length
)
{
    SECTION("Three-characters string")
    {
        static constexpr std::string_view const input{"cat"};

        STATIC_REQUIRE(longest_substring_length(input) == 3UZ);
    }
}
