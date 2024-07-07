// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/palindrome.hpp"
#include "forfun_c/palindrome.h"

namespace {

[[nodiscard]] inline auto
is_palindrome_wrapper(std::string_view const s) noexcept -> bool
{
    return ::is_palindrome(s.data(), s.size()) != 0;
}

[[nodiscard]] inline auto
is_palindrome_ci_wrapper(std::string_view const s) noexcept -> bool
{
    return ::is_palindrome_ci(s.data(), s.size()) != 0;
}

} // namespace

using std::string_view_literals::operator""sv;

TEMPLATE_TEST_CASE_SIG(
    "Case-sensitive palindrome check",
    "[palindrome]",
    ((auto is_palindrome), is_palindrome),
    (is_palindrome_wrapper),
    (forfun::palindrome::functional::is_palindrome),
    (forfun::palindrome::functional::bloated::is_palindrome),
    (forfun::palindrome::iterator_based::is_palindrome),
    (forfun::palindrome::raw::is_palindrome))
{
    SECTION("Positive")
    {
        std::string_view const s{GENERATE(
            ""sv,
            "\xb8Y\xb8"sv,
            "aa"sv,
            "aba"sv,
            "a b a"sv,
            "101"sv,
            "tattarrattat"sv,
            "ABBA"sv,
            "Xyz 8 zyX"sv,
            "step on no pets"sv,
            "19/9/91"sv)};

        CAPTURE(s);

        REQUIRE(is_palindrome(s));
    }

    SECTION("Negative")
    {
        std::string_view const s{GENERATE(
            "Dummy"sv,
            "dummy"sv,
            "Aa"sv,
            "Aab4'{x{'4BaA"sv,
            "Abba"sv,
            "Tattarrattat"sv,
            "Malayalam"sv,
            "Xyz 8 zYX"sv,
            "Step on no pets"sv,
            "12/20/2021"sv)};

        CAPTURE(s);

        REQUIRE_FALSE(is_palindrome(s));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Case-insensitive palindrome check",
    "[palindrome]",
    ((auto is_palindrome_ci), is_palindrome_ci),
    (is_palindrome_ci_wrapper),
    (forfun::palindrome::functional::bloated::is_palindrome_ci),
    (forfun::palindrome::iterator_based::is_palindrome_ci),
    (forfun::palindrome::raw::is_palindrome_ci))
{
    SECTION("Positive")
    {
        std::string_view const s{GENERATE(
            ""sv,
            "\xb8Y\xb8"sv,
            "aa"sv,
            "aba"sv,
            "a b a"sv,
            "101"sv,
            "Malayalam"sv,
            "tattarrattat"sv,
            "Tattarrattat"sv,
            "Aa"sv,
            "a b A"sv,
            "tattarratTat"sv,
            "Aab4'{x{'4BaA"sv,
            "Step on no pets"sv,
            "19/9/91"sv)};

        CAPTURE(s);

        REQUIRE(is_palindrome_ci(s));
    }

    SECTION("Negative")
    {
        std::string_view const s{GENERATE(
            "Dummy"sv,
            "dummy"sv,
            "42"sv,
            "12/20/2021"sv,
            "Step on no pets!"sv,
            " 010"sv,
            "Cat"sv)};

        CAPTURE(s);

        REQUIRE_FALSE(is_palindrome_ci(s));
    }
}
