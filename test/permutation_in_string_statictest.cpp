// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/permutation_in_string.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Permutation in string",
    "[permutation_in_string]",
    (auto check_inclusion, check_inclusion),
    forfun::permutation_in_string::check_inclusion,
    forfun::permutation_in_string::experimental::check_inclusion
)
{
    SECTION("One character which exists")
    {
        static constexpr std::string_view const needle{"h"};
        static constexpr std::string_view const haystack{"h"};

        STATIC_REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("One character which does not exists")
    {
        static constexpr std::string_view const needle{"q"};
        static constexpr std::string_view const haystack{"w"};

        STATIC_REQUIRE_FALSE(check_inclusion(needle, haystack));
    }
}
