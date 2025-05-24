// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <string>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "catch2_custom/matchers.hpp"

#include "forfun/group_anagrams.hpp"

TEST_CASE("Group anagrams", "[group_anagrams]")
{
    using forfun::testing::catch2_custom::matchers::UnorderedNestedRangeEquals;

    using forfun::group_anagrams::group_anagrams;

    SECTION("One element which is an empty string")
    {
        std::array<std::string, 1> const input{{""}};
        std::vector<std::vector<std::string>> const expected{{""}};

        CAPTURE(input);

        REQUIRE(group_anagrams(input.cbegin(), input.cend()) == expected);
    }

    SECTION("One element which is a string of one character")
    {
        std::array<std::string, 1> const input{"x"};
        std::vector<std::vector<std::string>> const expected{{"x"}};

        CAPTURE(input);

        REQUIRE(group_anagrams(input.cbegin(), input.cend()) == expected);
    }

    SECTION("Two elements which are not anagrams of each other")
    {
        std::array<std::string, 2> const input{"cat", "dog"};
        std::vector<std::vector<std::string>> const expected{{"cat"}, {"dog"}};

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("Two elements which are synogram of each other")
    {
        std::array<std::string, 2> const input{"note", "tone"};
        std::vector<std::vector<std::string>> const expected{{"note", "tone"}};

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("Three elements which are all anagrams of each other")
    {
        std::array<std::string, 3> const input{"ether", "there", "three"};
        std::vector<std::vector<std::string>> const expected{
            {"ether", "there", "three"}
        };

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("Three elements, two of which are antigrams of each other")
    {
        std::array<std::string, 3> const input{"united", "abcdef", "untied"};
        std::vector<std::vector<std::string>> const expected{
            {"abcdef"}, {"united", "untied"}
        };

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("Three elements, all of which are not anagrams of each other")
    {
        std::array<std::string, 3> const input{"always", "live", "consciously"};
        std::vector<std::vector<std::string>> const expected{
            {"always"}, {"live"}, {"consciously"}
        };

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("Thirty-two elements (benchmark case)")
    {
        std::array<std::string, 32> const input{
            "abcd",    "cadb", "no",   "xyz",  "anagram", "silent",
            "listen",  "zyx",  "xzy",  "abcd", "cat",     "bcda",
            "nagaram", "xyz",  "yxz",  "xyz",  "",        "anagram",
            "dabc",    "cat",  "abcd", "",     "nagaram", "zxy",
            "abcd",    "abcd", "cdab", "abcd", "xyz",     "abdc",
            "on",      "abcd"
        };
        std::vector<std::vector<std::string>> const expected{{
            // clang-format off
                {"", ""},
                {"no", "on"},
                {"cat", "cat"},
                {"anagram", "nagaram", "nagaram", "anagram"},
                {"listen", "silent"},
                {"xyz", "zyx", "xyz", "xzy", "xyz", "yxz", "xyz", "zxy"},
                {"abcd", "abcd", "abcd", "dabc", "abcd", "cdab", "abcd", "bcda",
                    "abcd", "abdc", "abcd", "cadb"},
            // clang-format on
        }};

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("LeetCode case 1")
    {
        std::array<std::string, 6> const input{
            "eat", "tea", "tan", "ate", "nat", "bat"
        };
        std::vector<std::vector<std::string>> const expected{
            {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}
        };

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }

    SECTION("NeetCode case 1")
    {
        std::array<std::string, 6> const input{
            "act", "pots", "tops", "cat", "stop", "hat"
        };
        std::vector<std::vector<std::string>> const expected{
            {"hat"}, {"act", "cat"}, {"pots", "stop", "tops"}
        };

        CAPTURE(input);

        REQUIRE_THAT(
            group_anagrams(input.cbegin(), input.cend()),
            UnorderedNestedRangeEquals(expected)
        );
    }
}

// References:
// - https://neetcode.io/problems/anagram-groups
// - https://leetcode.com/problems/group-anagrams/
