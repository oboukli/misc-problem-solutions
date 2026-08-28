// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_message.hpp>
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
    SECTION("One-character string")
    {
        static constexpr std::string_view const input{"x"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 1UZ);
    }

    SECTION("Two-characters string (case 1)")
    {
        static constexpr std::string_view const input{"ok"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 2UZ);
    }

    SECTION("Two-characters string (case 2)")
    {
        static constexpr std::string_view const input{"cc"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 1UZ);
    }

    SECTION("Three-characters string (case 1)")
    {
        static constexpr std::string_view const input{"cat"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Three-characters string (case 2)")
    {
        static constexpr std::string_view const input{"bff"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 2UZ);
    }

    SECTION("Three-characters string (case 3)")
    {
        static constexpr std::string_view const input{"eel"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 2UZ);
    }

    SECTION("Three-characters string (case 4)")
    {
        static constexpr std::string_view const input{"mmm"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 1UZ);
    }

    SECTION("Four-characters string (case 1)")
    {
        static constexpr std::string_view const input{"home"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 4UZ);
    }

    SECTION("Four-characters string (case 2)")
    {
        static constexpr std::string_view const input{"abba"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 2UZ);
    }

    SECTION("Four-characters string (case 3)")
    {
        static constexpr std::string_view const input{"dvdf"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Four-characters string (case 4)")
    {
        static constexpr std::string_view const input{"HHHH"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 1UZ);
    }

    SECTION("Five characters string (case 1)")
    {
        static constexpr std::string_view const input{"@@@@@"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 1UZ);
    }

    SECTION("Six-characters string (case 1)")
    {
        static constexpr std::string_view const input{"3123123"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Six-characters string (case 2)")
    {
        static constexpr std::string_view const input{"efghij"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 6UZ);
    }

    SECTION("Six-characters string (case 3)")
    {
        static constexpr std::string_view const input{"Sb%mSt"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 5UZ);
    }

    SECTION("Six-characters string (case 4)")
    {
        static constexpr std::string_view const input{"g33^y3"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Six-characters string (case 5)")
    {
        static constexpr std::string_view const input{"aabcde"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 5UZ);
    }

    SECTION("Seven-characters string (case 1)")
    {
        static constexpr std::string_view const input{"#6619b#"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 5UZ);
    }

    SECTION("Seven-characters string (case 2)")
    {
        static constexpr std::string_view const input{"aabccde"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Eight-characters string (case 1)")
    {
        static constexpr std::string_view const input{"abcabcbb"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 3UZ);
    }

    SECTION("Eight-characters string (case 2)")
    {
        static constexpr std::string_view const input{"abcaefgh"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 7UZ);
    }

    SECTION("Eight-characters string (case 3)")
    {
        static constexpr std::string_view const input{"abbaefgh"};

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 6UZ);
    }

    SECTION("String of 256 characters")
    {
        static constexpr std::string_view const input{
            "00000000000000000000abcabcbbxxxxxxxxxxxxxxxxxxxxxxxxxx000000000000"
            "00000000xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
            "xxxxxxxxxxxxabcdefghijkkabcdefghijlmnopXabcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZXXXXXXXXXXXXXXXXXXxxxx0000000000"
        };

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 52UZ);
    }

    SECTION("String of 1024 characters (benchmark case)")
    {
        static constexpr std::string_view const input{
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxy"
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567899"
        };

        CAPTURE(input);

        REQUIRE(longest_substring_length(input) == 62UZ);
    }
}
