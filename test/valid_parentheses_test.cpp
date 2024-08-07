// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/valid_parentheses.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Valid parentheses",
    "[valid_parentheses]",
    (auto is_valid, is_valid),
    forfun::valid_parentheses::ascii_optimized::is_valid,
    forfun::valid_parentheses::circuit_breaker::is_valid,
    forfun::valid_parentheses::deque_based::is_valid,
    forfun::valid_parentheses::dyn_array_based::is_valid,
    forfun::valid_parentheses::vector_based::is_valid,
    forfun::valid_parentheses::vector_based_demi_allocated::is_valid)
{
    SECTION("Valid")
    {
        SECTION("Empty string")
        {
            constexpr std::u8string_view const s{};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("()")
        {
            constexpr std::u8string_view const s{u8"()"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("[]")
        {
            constexpr std::u8string_view const s{u8"[]"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("{}")
        {
            constexpr std::u8string_view const s{u8"{}"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("()[]{}")
        {
            constexpr std::u8string_view const s{u8"()[]{}"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("(())")
        {
            constexpr std::u8string_view const s{u8"(())"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("([{}])")
        {
            constexpr std::u8string_view const s{u8"([{}])"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("[]{{{{{()}}}}}(([[[[]]]]))")
        {
            constexpr std::u8string_view const s{
                u8"[]{{{{{()}}}}}(([[[[]]]]))"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }

        SECTION("Benchmark valid case")
        {
            constexpr std::u8string_view const s{
                u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                "))))))))))))))))]]]]]]]]]]]]]]]]"};

            CAPTURE(s);

            REQUIRE(is_valid(s));
        }
    }

    SECTION("Invalid and of odd size")
    {
        SECTION("(")
        {
            constexpr std::u8string_view const s{u8"("};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION(")")
        {
            constexpr std::u8string_view const s{u8")"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("[")
        {
            constexpr std::u8string_view const s{u8"["};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("]")
        {
            constexpr std::u8string_view const s{u8"]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("{")
        {
            constexpr std::u8string_view const s{u8"{"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("}")
        {
            constexpr std::u8string_view const s{u8"}"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("(()")
        {
            constexpr std::u8string_view const s{u8"(()"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("{[(")
        {
            constexpr std::u8string_view const s{u8"{[("};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("})]")
        {
            constexpr std::u8string_view const s{u8"})]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("(){}[")
        {
            constexpr std::u8string_view const s{u8"(){}["};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("(})")
        {
            constexpr std::u8string_view const s{u8"(})"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("(({((})))")
        {
            constexpr std::u8string_view const s{u8"(({((})))"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }
    }

    SECTION("Invalid and of even size")
    {
        SECTION("(]")
        {
            constexpr std::u8string_view const s{u8"(]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("{{")
        {
            constexpr std::u8string_view const s{u8"{{"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("]]")
        {
            constexpr std::u8string_view const s{u8"]]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("([{)}]")
        {
            constexpr std::u8string_view const s{u8"([{)}]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }

        SECTION("Benchmark invalid case")
        {
            constexpr std::u8string_view const s{
                u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                "))))))))))))))))]]]]]]]]]]]]]]]"};

            CAPTURE(s);

            REQUIRE_FALSE(is_valid(s));
        }
    }

    SECTION("Malformed input")
    {
        constexpr std::u8string_view const s{u8"Malformed input"};

        CAPTURE(s);

        REQUIRE_FALSE(is_valid(s));
    }
}
