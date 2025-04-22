// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/valid_anagram.hpp"

using std::string_view_literals::operator""sv;

TEMPLATE_TEST_CASE_SIG(
    "Valid anagram (char ordinal comparison)",
    "[valid_anagram]",
    (auto is_anagram, is_anagram),
    forfun::valid_anagram::char_only::is_anagram,
    forfun::valid_anagram::generic::is_anagram<char>
)
{
    SECTION("Positive")
    {
        auto [s, t]{GENERATE(
            table<std::string_view, std::string_view>({
                {""sv, ""sv},
                {"cat"sv, "cat"sv},
                {"anagram"sv, "nagaram"sv}, // Benchmark case
                {"nagaram"sv, "anagram"sv},
                {"listen"sv, "silent"sv},
                {"abaa"sv, "aaba"sv},

                {"xyz"sv, "zyx"sv},
                {"xyz"sv, "xzy"sv},
                {"xyz"sv, "yxz"sv},
                {"xyz"sv, "zxy"sv},

                {"abcd"sv, "abcd"sv},
                {"abcd"sv, "dabc"sv},
                {"abcd"sv, "cdab"sv},
                {"abcd"sv, "bcda"sv},

                {"abcd"sv, "bacd"sv},
                {"abcd"sv, "dbac"sv},
                {"abcd"sv, "cdba"sv},
                {"abcd"sv, "acdb"sv},

                {"abcd"sv, "cbad"sv},
                {"abcd"sv, "dcba"sv},
                {"abcd"sv, "adcb"sv},
                {"abcd"sv, "badc"sv},

                {"abcd"sv, "abdc"sv},
                {"abcd"sv, "cadb"sv},
                {"abcd"sv, "bcad"sv},
                {"abcd"sv, "dbca"sv},
                {"abcd"sv, "adbc"sv},
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE(is_anagram(s, t));
    }

    SECTION("Negative")
    {
        auto [s, t]{GENERATE(
            table<std::string_view, std::string_view>({
                {"car"sv, "cat"sv},
                {"tiger"sv, "lion"sv},

                {"Cat"sv, "cat"sv},

                {"anagram"sv, "anagramanagram"sv},
                {"anagramanagram"sv, "anagram"sv},

                {"anagram"sv, "ana gram"sv},
                {"ana gram"sv, "anagram"sv},

                {"anagram"sv, "anagramcat"sv},
                {"anagramcat"sv, "anagram"sv},

                {"anagram"sv, "anagramlion"sv},
                {"anagramlion"sv, "anagram"sv},
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE_FALSE(is_anagram(s, t));
    }
}

TEST_CASE("Valid anagram (8-bit ordinal comparison)", "[valid_anagram]")
{
    using forfun::valid_anagram::generic::is_anagram;

    SECTION("Positive")
    {
        auto [s, t]{GENERATE(
            table<std::u8string_view, std::u8string_view>({
                {u8""sv, u8""sv},
                {u8"cat"sv, u8"cat"sv},
                {u8"anagram"sv, u8"nagaram"sv}, // Benchmark case
                {u8"nagaram"sv, u8"anagram"sv},
                {u8"listen"sv, u8"silent"sv},

                {u8"xyz"sv, u8"zyx"sv},
                {u8"xyz"sv, u8"xzy"sv},
                {u8"xyz"sv, u8"yxz"sv},
                {u8"xyz"sv, u8"zxy"sv},

                {u8"abcd"sv, u8"abcd"sv},
                {u8"abcd"sv, u8"dabc"sv},
                {u8"abcd"sv, u8"cdab"sv},
                {u8"abcd"sv, u8"bcda"sv},

                {u8"abcd"sv, u8"bacd"sv},
                {u8"abcd"sv, u8"dbac"sv},
                {u8"abcd"sv, u8"cdba"sv},
                {u8"abcd"sv, u8"acdb"sv},

                {u8"abcd"sv, u8"cbad"sv},
                {u8"abcd"sv, u8"dcba"sv},
                {u8"abcd"sv, u8"adcb"sv},
                {u8"abcd"sv, u8"badc"sv},

                {u8"abcd"sv, u8"abdc"sv},
                {u8"abcd"sv, u8"cadb"sv},
                {u8"abcd"sv, u8"bcad"sv},
                {u8"abcd"sv, u8"dbca"sv},
                {u8"abcd"sv, u8"adbc"sv},

                {u8"عربي"sv, u8"عبري"sv}, //  Arabic <=> Hebrew
                {u8"我爱你"sv, u8"你爱我"sv}, // I love you <=> You love me
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE(is_anagram(s, t));
    }

    SECTION("Negative")
    {
        auto [s, t]{GENERATE(
            table<std::u8string_view, std::u8string_view>({
                {u8"car"sv, u8"cat"sv},
                {u8"tiger"sv, u8"lion"sv},

                {u8"Cat"sv, u8"cat"sv},

                {u8"anagram"sv, u8"anagramanagram"sv},
                {u8"anagramanagram"sv, u8"anagram"sv},

                {u8"anagram"sv, u8"ana gram"sv},
                {u8"ana gram"sv, u8"anagram"sv},

                {u8"anagram"sv, u8"anagramcat"sv},
                {u8"anagramcat"sv, u8"anagram"sv},

                {u8"anagram"sv, u8"anagramlion"sv},
                {u8"anagramlion"sv, u8"anagram"sv},
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE_FALSE(is_anagram(s, t));
    }
}

TEST_CASE("Valid anagram (32-bit ordinal comparison)", "[valid_anagram]")
{
    using forfun::valid_anagram::generic::is_anagram;

    SECTION("Positive")
    {
        auto [s, t]{GENERATE(
            table<std::u32string_view, std::u32string_view>({
                {U""sv, U""sv},
                {U"cat"sv, U"cat"sv},
                {U"anagram"sv, U"nagaram"sv}, // Benchmark case
                {U"nagaram"sv, U"anagram"sv},
                {U"listen"sv, U"silent"sv},

                {U"xyz"sv, U"zyx"sv},
                {U"xyz"sv, U"xzy"sv},
                {U"xyz"sv, U"yxz"sv},
                {U"xyz"sv, U"zxy"sv},

                {U"abcd"sv, U"abcd"sv},
                {U"abcd"sv, U"dabc"sv},
                {U"abcd"sv, U"cdab"sv},
                {U"abcd"sv, U"bcda"sv},

                {U"abcd"sv, U"bacd"sv},
                {U"abcd"sv, U"dbac"sv},
                {U"abcd"sv, U"cdba"sv},
                {U"abcd"sv, U"acdb"sv},

                {U"abcd"sv, U"cbad"sv},
                {U"abcd"sv, U"dcba"sv},
                {U"abcd"sv, U"adcb"sv},
                {U"abcd"sv, U"badc"sv},

                {U"abcd"sv, U"abdc"sv},
                {U"abcd"sv, U"cadb"sv},
                {U"abcd"sv, U"bcad"sv},
                {U"abcd"sv, U"dbca"sv},
                {U"abcd"sv, U"adbc"sv},

                {U"عربي"sv, U"عبري"sv}, //  Arabic <=> Hebrew
                {U"我爱你"sv, U"你爱我"sv}, // I love you <=> You love me
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE(is_anagram(s, t));
    }

    SECTION("Negative")
    {
        auto [s, t]{GENERATE(
            table<std::u32string_view, std::u32string_view>({
                {U"car"sv, U"cat"sv},
                {U"tiger"sv, U"lion"sv},

                {U"Cat"sv, U"cat"sv},

                {U"anagram"sv, U"anagramanagram"sv},
                {U"anagramanagram"sv, U"anagram"sv},

                {U"anagram"sv, U"ana gram"sv},
                {U"ana gram"sv, U"anagram"sv},

                {U"anagram"sv, U"anagramcat"sv},
                {U"anagramcat"sv, U"anagram"sv},

                {U"anagram"sv, U"anagramlion"sv},
                {U"anagramlion"sv, U"anagram"sv},
            })
        )};

        CAPTURE(s);
        CAPTURE(t);

        REQUIRE_FALSE(is_anagram(s, t));
    }
}
