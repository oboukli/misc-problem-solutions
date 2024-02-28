// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/palindrome.h"
#include "forfun/palindrome.hpp"

namespace {

[[nodiscard]] inline bool
is_palindrome_wrapper(std::string_view const& s) noexcept
{
    return ::is_palindrome(s.data(), s.size());
}

[[nodiscard]] inline bool
is_palindrome_ci_wrapper(std::string_view const& s) noexcept
{
    return ::is_palindrome_ci(s.data(), s.size());
}

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Case-sensitive palindrome check",
    "[palindrome]",
    ((auto is_palindrome), is_palindrome),
    (forfun::palindrome::fast::is_palindrome),
    (forfun::palindrome::stl_bloated::is_palindrome),
    (forfun::palindrome::stl_fast::is_palindrome),
    (forfun::palindrome::raw::is_palindrome),
    (is_palindrome_wrapper))
{
    SECTION("Positive")
    {
        std::string_view s{GENERATE(
            "",
            "\xb8Y\xb8",
            "aa",
            "aba",
            "a b a",
            "101",
            "tattarrattat",
            "ABBA",
            "Xyz 8 zyX",
            "step on no pets",
            "19/9/91")};

        CAPTURE(s);

        REQUIRE(is_palindrome(s));
    }

    SECTION("Negative")
    {
        std::string_view s{GENERATE(
            "Dummy",
            "dummy",
            "Aa",
            "Aab4'{x{'4BaA",
            "Abba",
            "Tattarrattat",
            "Malayalam"
            "Xyz 8 zYX",
            "Step on no pets",
            "12/20/2021")};

        CAPTURE(s);

        REQUIRE_FALSE(is_palindrome(s));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Case-insensitive palindrome check",
    "[palindrome]",
    ((auto is_palindrome_ci), is_palindrome_ci),
    (forfun::palindrome::fast::is_palindrome_ci),
    (forfun::palindrome::raw::is_palindrome_ci),
    (is_palindrome_ci_wrapper))
{
    SECTION("Positive")
    {
        std::string_view s{GENERATE(
            "",
            "\xb8Y\xb8",
            "aa",
            "aba",
            "a b a",
            "101",
            "Malayalam",
            "tattarrattat",
            "Tattarrattat",
            "Aa",
            "a b A",
            "tattarratTat",
            "Aab4'{x{'4BaA",
            "Step on no pets",
            "19/9/91")};

        CAPTURE(s);

        REQUIRE(is_palindrome_ci(s));
    }

    SECTION("Negative")
    {
        std::string_view s{GENERATE(
            "Dummy",
            "dummy",
            "42",
            "12/20/2021",
            "Step on no pets!",
            " 010",
            "Cat")};

        CAPTURE(s);

        REQUIRE_FALSE(is_palindrome_ci(s));
    }
}
