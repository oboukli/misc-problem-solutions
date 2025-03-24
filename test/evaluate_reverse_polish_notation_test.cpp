// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>
#include <system_error>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/evaluate_reverse_polish_notation.hpp"

using std::string_view_literals::operator""sv;

using VecConstIter = std::vector<std::string_view>::const_iterator;

TEMPLATE_TEST_CASE_SIG(
    "Evaluate reverse polish notation (Well-formed input)",
    "[evaluate_reverse_polish_notation]",
    (auto eval_expression, eval_expression),
    // clang-format off
    (forfun::evaluate_reverse_polish_notation::hardened::
        eval_expression<VecConstIter, VecConstIter>),
    (forfun::evaluate_reverse_polish_notation::speed_optimized::
        eval_expression<VecConstIter, VecConstIter>),
    (forfun::evaluate_reverse_polish_notation::unhardened::
        eval_expression<VecConstIter, VecConstIter>)
    // clang-format on
)
{
    SECTION("Empty")
    {
        std::vector<std::string_view> const tokens{};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == 0);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Return as is")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"0"sv}, 0},
                {{"1"sv}, 1},
                {{"2"sv}, 2},
                {{"11"sv}, 11},
                {{"-1"sv}, -1},
                {{"-17"sv}, -17},
                {{"7919"sv}, 7919},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Addition")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"0"sv, "0"sv, "+"sv}, 0},
                {{"0"sv, "1"sv, "+"sv}, 1},
                {{"1"sv, "0"sv, "+"sv}, 1},
                {{"1"sv, "1"sv, "+"sv}, 2},
                {{"0"sv, "23"sv, "+"sv}, 23},
                {{"23"sv, "0"sv, "+"sv}, 23},
                {{"3"sv, "17"sv, "+"sv}, 20},
                {{"17"sv, "3"sv, "+"sv}, 20},
                {{"1000"sv, "1"sv, "+"sv}, 1001},
                {{"1"sv, "1000"sv, "+"sv}, 1001},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Subtraction")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"0"sv, "0"sv, "-"sv}, 0},
                {{"1"sv, "1"sv, "-"sv}, 0},
                {{"1"sv, "0"sv, "-"sv}, 1},
                {{"0"sv, "1"sv, "-"sv}, -1},
                {{"3"sv, "17"sv, "-"sv}, -14},
                {{"17"sv, "3"sv, "-"sv}, 14},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Multiplication")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"0"sv, "0"sv, "*"sv}, 0},
                {{"0"sv, "1"sv, "*"sv}, 0},
                {{"1"sv, "0"sv, "*"sv}, 0},
                {{"1"sv, "1"sv, "*"sv}, 1},
                {{"1"sv, "311"sv, "*"sv}, 311},
                {{"311"sv, "1"sv, "*"sv}, 311},
                {{"3"sv, "17"sv, "*"sv}, 51},
                {{"17"sv, "3"sv, "*"sv}, 51},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Division (valid cases)")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"1"sv, "1"sv, "/"sv}, 1},
                {{"3"sv, "17"sv, "/"sv}, 0},
                {{"17"sv, "3"sv, "/"sv}, 5},
                {{"0"sv, "41"sv, "/"sv}, 0},
                {{"0"sv, "-41"sv, "/"sv}, 0},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Values only")
    {
        auto [tokens, expected]{GENERATE(
            table<std::vector<std::string_view>, int>({
                {{"17"sv, "0"sv}, 0},
                {{"157"sv, "163"sv}, 163},
                {{"19"sv, "-7"sv}, -7},
                {{"-19"sv, "7"sv}, 7},
                {{"-15"sv, "-31"sv}, -31},
                {{"1"sv, "1"sv}, 1},
                {{"1"sv, "1"sv, "1"sv}, 1},
                {{"3"sv, "17"sv, "0"sv}, 0},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == expected);
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("(((((((211 - 283) - 137) * 47) / 241) + 113) - 67) * 89)")
    {
        std::vector<std::string_view> const tokens{
            "211"sv,
            "283"sv,
            "-"sv,
            "137"sv,
            "-"sv,
            "47"sv,
            "*"sv,
            "241"sv,
            "/"sv,
            "113"sv,
            "+"sv,
            "67"sv,
            "-"sv,
            "89"sv,
            "*"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(
            actual_result
            == (((((((211 - 283) - 137) * 47) / 241) + 113) - 67) * 89)
        );
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("Invalid operator")
    {
        std::vector<std::string_view> const tokens{{"1"sv, "1"sv, "#"sv}};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION(
        "((((((((149 * 2) + 61) + 223) - 2) / 11) + 71) * 293) - 101) "
        "(benchmark case)"
    )
    {
        std::vector<std::string_view> const tokens{
            "149"sv,
            "2"sv,
            "*"sv,
            "61"sv,
            "+"sv,
            "223"sv,
            "+"sv,
            "-2"sv,
            "+"sv,
            "11"sv,
            "/"sv,
            "71"sv,
            "+"sv,
            "293"sv,
            "*"sv,
            "101"sv,
            "-"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(
            actual_result
            == ((((((((149 * 2) + 61) + 223) - 2) / 11) + 71) * 293) - 101)
        );
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("LeetCode case 1")
    {
        std::vector<std::string_view> const tokens{
            "2"sv, "1"sv, "+"sv, "3"sv, "*"sv
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == ((2 + 1) * 3));
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("LeetCode case 2")
    {
        std::vector<std::string_view> const tokens{
            "4"sv, "13"sv, "5"sv, "/"sv, "+"sv
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == (4 + (13 / 5)));
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("LeetCode case 3")
    {
        std::vector<std::string_view> const tokens{
            "10"sv,
            "6"sv,
            "9"sv,
            "3"sv,
            "+"sv,
            "-11"sv,
            "*"sv,
            "/"sv,
            "*"sv,
            "17"sv,
            "+"sv,
            "5"sv,
            "+"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == ((10 * (6 / ((9 + 3) * -11))) + 17) + 5);
        REQUIRE(actual_error == std::errc{});
    }
}

TEST_CASE(
    "Evaluate reverse polish notation (Invalid input)",
    "[evaluate_reverse_polish_notation]"
)
{
    using forfun::evaluate_reverse_polish_notation::hardened::eval_expression;

    SECTION("Division by zero")
    {
        std::vector<std::string_view> const tokens{"1093"sv, "0"sv, "/"sv};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Invalid operator")
    {
        auto [tokens]{GENERATE(
            table<std::vector<std::string_view>>({
                {{"3"sv, "17"sv, "@"sv}},
                {{"17"sv, "3"sv, "="sv}},
                {{"0"sv, "41"sv, "A"sv}},
                {{"0"sv, "-41"sv, "b"sv}},
                {{"0"sv, "-41"sv, ""sv}},
                {{"0"sv, "-41"sv, "  "sv}},
                {{"0"sv, "-41"sv, " + "sv}},
                {{"0"sv, "-41"sv, "++"sv}},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Invalid operands")
    {
        auto [tokens]{GENERATE(
            table<std::vector<std::string_view>>({
                {{" 0"sv, "0"sv, "+"sv}},
                {{"0 "sv, "1"sv, "+"sv}},
                {{"1"sv, "1 1"sv, "+"sv}},
                {{"1"sv, " 0 "sv, "+"sv}},
                {{"3"sv, "n"sv, "+"sv}},
                {{""sv, ""sv, "+"sv}},
                {{"n"sv, ""sv, "-"sv}},
                {{"a"sv, "b"sv, "/"sv}},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Malformed input")
    {
        auto [tokens]{GENERATE(
            table<std::vector<std::string_view>>({
                {{""sv}},
                {{"0"sv, "0"sv, "++"sv}},
                {{"invalid input"sv}},
                {{"17"sv, "invalid input"sv, "+"sv}},
                {{"0"sv, "41"sv, "invalid input"sv}},
                {{"invalid input"sv, "invalid input"sv, "invalid input"sv}},
            })
        )};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Overflow case 1")
    {
        std::vector<std::string_view> const tokens{
            "-2147483648"sv,
            "-1"sv,
            "/"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Overflow case 2")
    {
        std::vector<std::string_view> const tokens{
            "2147483647"sv,
            "1"sv,
            "+"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Overflow case 3")
    {
        std::vector<std::string_view> const tokens{
            "2147483647"sv,
            "10"sv,
            "*"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }

    SECTION("Overflow case 4")
    {
        std::vector<std::string_view> const tokens{
            "0"sv,
            "2147483647"sv,
            "-"sv,
            "2"sv,
            "-"sv,
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::invalid_argument);
    }
}
