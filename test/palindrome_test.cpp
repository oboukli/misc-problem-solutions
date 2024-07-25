// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>
#include <utility>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/palindrome.hpp"
#include "forfun_c/palindrome.h"

namespace {

template <typename Func, Func func, typename BasicStringView>
[[nodiscard]] constexpr auto
adapt_func_is_palindrome(BasicStringView&& s) noexcept -> bool
{
    if constexpr (std::is_invocable_r_v<bool, decltype(func), decltype(s)>)
    {
        return func(std::forward<decltype(s)>(s));
    }
    // clang-format off
    else if constexpr (std::is_invocable_r_v<
        bool, decltype(func), decltype(s.data()), decltype(s.length())>)
    // clang-format on
    {
        return func(
            std::forward<decltype(s.data())>(s.data()),
            std::forward<decltype(s.length())>(s.length()));
    }
}

} // namespace

using std::string_view_literals::operator""sv;

TEMPLATE_TEST_CASE_SIG(
    "Case-sensitive palindrome check",
    "[palindrome]",
    ((auto func_is_palindrome), func_is_palindrome),
    (&::is_palindrome),
    (&forfun::palindrome::functional::is_palindrome<char>),
    (&forfun::palindrome::functional::bloated::is_palindrome<char>),
    (&forfun::palindrome::iterator_based::is_palindrome<char>),
    (&forfun::palindrome::offset_based::is_palindrome<char>))
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

        // clang-format off
        REQUIRE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
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

        // clang-format off
        REQUIRE_FALSE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Case-sensitive palindrome check (wchar_t)",
    "[palindrome]",
    ((auto func_is_palindrome), func_is_palindrome),
    (&forfun::palindrome::functional::is_palindrome<wchar_t>),
    (&forfun::palindrome::functional::bloated::is_palindrome<wchar_t>),
    (&forfun::palindrome::iterator_based::is_palindrome<wchar_t>),
    (&forfun::palindrome::offset_based::is_palindrome<wchar_t>))
{
    SECTION("Positive")
    {
        std::basic_string_view<wchar_t> const s{GENERATE(
            L""sv,
            L"\xb8Y\xb8"sv,
            L"aa"sv,
            L"aba"sv,
            L"a b a"sv,
            L"101"sv,
            L"tattarrattat"sv,
            L"ABBA"sv,
            L"Xyz 8 zyX"sv,
            L"step on no pets"sv,
            L"باب"sv, // Door, in Arabic
            L"亞細亞"sv, // Asia, in Chinese
            L"19/9/91"sv)};

        CAPTURE(s);

        // clang-format off
        REQUIRE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
    }

    SECTION("Negative")
    {
        std::basic_string_view<wchar_t> const s{GENERATE(
            L"Dummy"sv,
            L"dummy"sv,
            L"Aa"sv,
            L"Aab4'{x{'4BaA"sv,
            L"Abba"sv,
            L"Tattarrattat"sv,
            L"Malayalam"sv,
            L"Xyz 8 zYX"sv,
            L"Step on no pets"sv,
            L"قطة"sv, // Cat, in Arabic
            L"12/20/2021"sv)};

        CAPTURE(s);

        // clang-format off
        REQUIRE_FALSE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Case-sensitive palindrome check (char32_t)",
    "[palindrome]",
    ((auto func_is_palindrome), func_is_palindrome),
    (&forfun::palindrome::functional::is_palindrome<char32_t>),
    (&forfun::palindrome::functional::bloated::is_palindrome<char32_t>),
    (&forfun::palindrome::iterator_based::is_palindrome<char32_t>),
    (&forfun::palindrome::offset_based::is_palindrome<char32_t>))
{
    SECTION("Positive")
    {
        std::basic_string_view<char32_t> const s{GENERATE(
            U""sv,
            U"\xb8Y\xb8"sv,
            U"aa"sv,
            U"aba"sv,
            U"a b a"sv,
            U"101"sv,
            U"tattarrattat"sv,
            U"ABBA"sv,
            U"Xyz 8 zyX"sv,
            U"step on no pets"sv,
            U"باب"sv, // Door, in Arabic
            U"亞細亞"sv, // Asia, in Chinese
            U"19/9/91"sv)};

        CAPTURE(s);

        // clang-format off
        REQUIRE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
    }

    SECTION("Negative")
    {
        std::basic_string_view<char32_t> const s{GENERATE(
            U"Dummy"sv,
            U"dummy"sv,
            U"Aa"sv,
            U"Aab4'{x{'4BaA"sv,
            U"Abba"sv,
            U"Tattarrattat"sv,
            U"Malayalam"sv,
            U"Xyz 8 zYX"sv,
            U"Step on no pets"sv,
            U"قطة"sv, // Cat, in Arabic
            U"12/20/2021"sv)};

        CAPTURE(s);

        // clang-format off
        REQUIRE_FALSE(adapt_func_is_palindrome<
            decltype(func_is_palindrome),
            func_is_palindrome>(s));
        // clang-format on
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Case-insensitive palindrome check",
    "[palindrome]",
    ((auto func_is_palindrome_ci), func_is_palindrome_ci),
    (&::is_palindrome_ci),
    (&forfun::palindrome::functional::bloated::is_palindrome_ci),
    (&forfun::palindrome::iterator_based::is_palindrome_ci),
    (&forfun::palindrome::offset_based::is_palindrome_ci))
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

        // clang-format off
        REQUIRE(adapt_func_is_palindrome<
            decltype(func_is_palindrome_ci),
            func_is_palindrome_ci>(s));
        // clang-format on
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

        // clang-format off
        REQUIRE_FALSE(adapt_func_is_palindrome<
            decltype(func_is_palindrome_ci),
            func_is_palindrome_ci>(s));
        // clang-format on
    }
}
