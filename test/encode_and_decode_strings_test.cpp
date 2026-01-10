// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/encode_and_decode_strings.hpp"

TEST_CASE("Encode strings", "[encode_and_decode_strings]")
{
    using std::string_view_literals::operator""sv;
    using forfun::encode_and_decode_strings::delimited::encode;

    SECTION("Empty container")
    {
        std::vector<std::string> const tokens{};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view().empty());
    }

    SECTION("Exactly one element. Element is empty string")
    {
        std::vector<std::string> const tokens{""};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view().empty());
    }

    SECTION("One element")
    {
        std::vector<std::string> const tokens{{"One"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "One"sv);
    }

    SECTION("Two elements")
    {
        std::vector<std::string> const tokens{{"Two"}, {"2"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "Two 2"sv);
    }

    SECTION("Three elements")
    {
        std::vector<std::string> const tokens{{"Three"}, {"3"}, {"III"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "Three 3 III"sv);
    }

    SECTION("Four elements")
    {
        std::vector<std::string> const tokens{"these", "are", "four", "words"};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "these are four words"sv);
    }

    SECTION("Element ends in escaped escape character")
    {
        std::vector<std::string> const tokens{"these", "are", "four~", "words"};
        std::stringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "these are four~~ words"sv);
    }

    SECTION("Element ends in escaped delimiter character")
    {
        std::vector<std::string> const tokens{"these", "are ", "four", "words"};
        std::stringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "these are~  four words"sv);
    }

    SECTION("Escape and delimiter characters")
    {
        std::vector<std::string> const tokens{
            "w~e", "~are", "~four~", " t okens "
        };
        std::stringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "w~~e ~~are ~~four~~ ~ t~ okens~ "sv);
    }

    SECTION("One characters")
    {
        std::vector<std::string> const tokens{{"1"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "1"sv);
    }

    SECTION("Two characters")
    {
        std::vector<std::string> const tokens{{"12"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "12"sv);
    }

    SECTION("Three characters")
    {
        std::vector<std::string> const tokens{{"abc"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "abc"sv);
    }

    SECTION("Stand-alone escape character")
    {
        std::vector<std::string> const tokens{{"~"}};
        std::ostringstream ss{};

        CHECK(
            tokens.front().front()
            == forfun::encode_and_decode_strings::delimited::escape_char
        );

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "~~"sv);
    }

    SECTION("Stand-alone delimiter character")
    {
        std::vector<std::string> const tokens{{}, {}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == " "sv);
    }

    SECTION("Delimiter at the begining")
    {
        std::vector<std::string> const tokens{{""}, {"Hello"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == " Hello"sv);
    }

    SECTION("Two delimiters at the begining")
    {
        std::vector<std::string> const tokens{{""}, {""}, {"Hello"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "  Hello"sv);
    }

    SECTION("Delimiter at the end")
    {
        std::vector<std::string> const tokens{{"Hello"}, {""}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "Hello "sv);
    }

    SECTION("Two delimiters at the end")
    {
        std::vector<std::string> const tokens{{"Hello"}, {""}, {""}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "Hello  "sv);
    }

    SECTION("Delimiters, one at the begining and one at the end")
    {
        std::vector<std::string> const tokens{{""}, {"Hello"}, {""}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == " Hello "sv);
    }

    SECTION("Escape (case 1)")
    {
        std::vector<std::string> const tokens{{" "}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "~ "sv);
    }

    SECTION("Escape (case 2)")
    {
        std::vector<std::string> const tokens{{"Hello, World!"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "Hello,~ World!"sv);
    }

    SECTION("Escape (case 3)")
    {
        std::vector<std::string> const tokens{{"a   b ~ Z~~~"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "a~ ~ ~ b~ ~~~ Z~~~~~~"sv);
    }

    SECTION("Escape (case 4)")
    {
        std::vector<std::string> const tokens{{"a   "}, {"b ~ Z~~~"}};
        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view() == "a~ ~ ~  b~ ~~~ Z~~~~~~"sv);
    }

    SECTION("Escape (benchmark case)")
    {
        static constexpr std::array const tokens{
            // clang-format off
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"sv,
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"
            "abcd    ~~~~efghabcd    ~~~~efgh"sv,
            // clang-format on
        };
        static_assert(tokens.size() == 2UZ);
        static_assert(tokens.front().size() == 256UZ);
        static_assert(tokens.at(1).size() == 256UZ);

        std::ostringstream ss{};

        CAPTURE(tokens);

        encode(tokens.cbegin(), tokens.cend(), ss);

        REQUIRE(ss.view().size() == 769UZ);
        REQUIRE(
            ss.view() ==
            // clang-format off
            "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
            "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
            "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
            "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
            "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
            "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
            " abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
            "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
            " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
            "habcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
            "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
            " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
            "h"sv
            // clang-format on
        );
    }
}

TEST_CASE("Decode strings", "[encode_and_decode_strings]")
{
    using forfun::encode_and_decode_strings::delimited::decode;

    SECTION("Empty")
    {
        std::string_view const encoded{};

        CAPTURE(encoded);

        REQUIRE(decode(encoded).empty());
    }

    SECTION("One element")
    {
        std::string_view const encoded{"One"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"One"}});
    }

    SECTION("Two elements")
    {
        std::string_view const encoded{"Two 2"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"Two"}, {"2"}});
    }

    SECTION("Three elements")
    {
        std::string_view const encoded{"Three 3 III"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{{"Three"}, {"3"}, {"III"}}
        );
    }

    SECTION("Four elements")
    {
        std::string_view const encoded{"these are four words"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{"these", "are", "four", "words"}
        );
    }

    SECTION("Element ends in escaped escape character")
    {
        std::string_view const encoded{"these are four~~ words"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{"these", "are", "four~", "words"}
        );
    }

    SECTION("Element ends in escaped delimiter character")
    {
        std::string_view const encoded{"these are~ three tokens"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{"these", "are three", "tokens"}
        );
    }

    SECTION("Escape and delimiter characters")
    {
        std::string_view const encoded{"w~~e ~~are ~~four~~ ~ t~ okens~ "};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{"w~e", "~are", "~four~", " t okens "}
        );
    }

    SECTION("One characters")
    {
        std::string_view const encoded{"1"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"1"}});
    }

    SECTION("Two characters")
    {
        std::string_view const encoded{"12"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"12"}});
    }

    SECTION("Three characters")
    {
        std::string_view const encoded{"abc"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"abc"}});
    }

    SECTION("Stand-alone escape character")
    {
        static constexpr std::string_view const encoded{"~~"};
        static_assert(
            encoded.front()
            == forfun::encode_and_decode_strings::delimited::escape_char
        );

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"~"}});
    }

    SECTION("Stand-alone delimiter character")
    {
        static constexpr std::string_view const encoded{" "};
        static_assert(
            encoded.front()
            == forfun::encode_and_decode_strings::delimited::delimiter_char
        );

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{}, {}});
    }

    SECTION("Delimiter at the begining")
    {
        std::string_view const encoded{" Hello"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{""}, {"Hello"}});
    }

    SECTION("Two delimiters at the begining")
    {
        std::string_view const encoded{"  Hello"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded) == std::vector<std::string>{{""}, {""}, {"Hello"}}
        );
    }

    SECTION("Delimiter at the end")
    {
        std::string_view const encoded{"Hello "};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"Hello"}, {""}});
    }

    SECTION("Two delimiters at the end")
    {
        std::string_view const encoded{"Hello  "};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded) == std::vector<std::string>{{"Hello"}, {""}, {""}}
        );
    }

    SECTION("Delimiters, one at the begining and one at the end")
    {
        std::string_view const encoded{" Hello "};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded) == std::vector<std::string>{{""}, {"Hello"}, {""}}
        );
    }

    SECTION("Unescape (case 1)")
    {
        std::string_view const encoded{"~ "};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{" "}});
    }

    SECTION("Unescape (case 2)")
    {
        std::string_view const encoded{"Hello,~ World!"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"Hello, World!"}});
    }

    SECTION("Unescape (case 3)")
    {
        std::string_view const encoded{"a~ ~ ~ b~ ~~~ Z~~~~~~"};

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"a   b ~ Z~~~"}});
    }

    SECTION("Unescape (case 4)")
    {
        std::string_view const encoded{"a~ ~ ~  b~ ~~~ Z~~~~~~"};

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded) == std::vector<std::string>{{"a   "}, {"b ~ Z~~~"}}
        );
    }

    SECTION("Unescape (benchmark case)")
    {
        std::string_view const encoded{
            // clang-format off
            "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
            "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
            "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
            "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
            "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
            "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
            " abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
            "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
            " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
            "habcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
            "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
            " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
            "h"
            // clang-format on
        };

        CAPTURE(encoded);

        REQUIRE(
            decode(encoded)
            == std::vector<std::string>{
                // clang-format off
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh",
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh"
                "abcd    ~~~~efghabcd    ~~~~efgh",
                // clang-format on
            }
        );
    }

    SECTION("Invalid encoded string (case 1)")
    {
        static constexpr std::string_view const encoded{"~"};
        static_assert(
            encoded.front()
            == forfun::encode_and_decode_strings::delimited::escape_char
        );

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{""}});
    }

    SECTION("Invalid encoded string (case 2)")
    {
        static constexpr std::string_view const encoded{"~x"};
        static_assert(
            encoded.front()
            == forfun::encode_and_decode_strings::delimited::escape_char
        );

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{""}});
    }

    SECTION("Invalid encoded string (case 3)")
    {
        static constexpr std::string_view const encoded{"~~~"};
        static_assert(
            encoded.front()
            == forfun::encode_and_decode_strings::delimited::escape_char
        );

        CAPTURE(encoded);

        REQUIRE(decode(encoded) == std::vector<std::string>{{"~"}});
    }
}
