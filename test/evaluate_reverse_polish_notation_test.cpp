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

namespace {

using VecConstIter = std::vector<std::string_view>::const_iterator;

} // namespace

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
                {{"0"}, 0},
                {{"1"}, 1},
                {{"2"}, 2},
                {{"11"}, 11},
                {{"-1"}, -1},
                {{"-17"}, -17},
                {{"7919"}, 7919},
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
                {{"0", "0", "+"}, 0},
                {{"0", "1", "+"}, 1},
                {{"1", "0", "+"}, 1},
                {{"1", "1", "+"}, 2},
                {{"0", "23", "+"}, 23},
                {{"23", "0", "+"}, 23},
                {{"3", "17", "+"}, 20},
                {{"17", "3", "+"}, 20},
                {{"1000", "1", "+"}, 1001},
                {{"1", "1000", "+"}, 1001},
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
                {{"0", "0", "-"}, 0},
                {{"1", "1", "-"}, 0},
                {{"1", "0", "-"}, 1},
                {{"0", "1", "-"}, -1},
                {{"3", "17", "-"}, -14},
                {{"17", "3", "-"}, 14},
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
                {{"0", "0", "*"}, 0},
                {{"0", "1", "*"}, 0},
                {{"1", "0", "*"}, 0},
                {{"1", "1", "*"}, 1},
                {{"1", "311", "*"}, 311},
                {{"311", "1", "*"}, 311},
                {{"3", "17", "*"}, 51},
                {{"17", "3", "*"}, 51},
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
                {{"1", "1", "/"}, 1},
                {{"3", "17", "/"}, 0},
                {{"17", "3", "/"}, 5},
                {{"0", "41", "/"}, 0},
                {{"0", "-41", "/"}, 0},
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
                {{"17", "0"}, 0},
                {{"157", "163"}, 163},
                {{"19", "-7"}, -7},
                {{"-19", "7"}, 7},
                {{"-15", "-31"}, -31},
                {{"1", "1"}, 1},
                {{"1", "1", "1"}, 1},
                {{"3", "17", "0"}, 0},
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
            "211",
            "283",
            "-",
            "137",
            "-",
            "47",
            "*",
            "241",
            "/",
            "113",
            "+",
            "67",
            "-",
            "89",
            "*",
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
        std::vector<std::string_view> const tokens{{"1", "1", "#"}};

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
            "149",
            "2",
            "*",
            "61",
            "+",
            "223",
            "+",
            "-2",
            "+",
            "11",
            "/",
            "71",
            "+",
            "293",
            "*",
            "101",
            "-",
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
        std::vector<std::string_view> const tokens{"2", "1", "+", "3", "*"};

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_result == ((2 + 1) * 3));
        REQUIRE(actual_error == std::errc{});
    }

    SECTION("LeetCode case 2")
    {
        std::vector<std::string_view> const tokens{"4", "13", "5", "/", "+"};

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
            "10",
            "6",
            "9",
            "3",
            "+",
            "-11",
            "*",
            "/",
            "*",
            "17",
            "+",
            "5",
            "+",
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
    "Evaluate reverse polish notation (Invalid or out-of-domain input cases)",
    "[evaluate_reverse_polish_notation]"
)
{
    using forfun::evaluate_reverse_polish_notation::hardened::eval_expression;

    SECTION("Division by zero")
    {
        std::vector<std::string_view> const tokens{"1093", "0", "/"};

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
                {{"3", "17", "@"}},
                {{"17", "3", "="}},
                {{"0", "41", "A"}},
                {{"0", "-41", "b"}},
                {{"0", "-41", ""}},
                {{"0", "-41", "  "}},
                {{"0", "-41", " + "}},
                {{"0", "-41", "++"}},
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
                {{" 0", "0", "+"}},
                {{"0 ", "1", "+"}},
                {{"1", "1 1", "+"}},
                {{"1", " 0 ", "+"}},
                {{"3", "n", "+"}},
                {{"", "", "+"}},
                {{"n", "", "-"}},
                {{"a", "b", "/"}},
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
                {{""}},
                {{"0", "0", "++"}},
                {{"invalid input"}},
                {{"17", "invalid input", "+"}},
                {{"0", "41", "invalid input"}},
                {{"invalid input", "invalid input", "invalid input"}},
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
            "-2147483648",
            "-1",
            "/",
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::argument_out_of_domain);
    }

    SECTION("Overflow case 2")
    {
        std::vector<std::string_view> const tokens{
            "2147483647",
            "1",
            "+",
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::argument_out_of_domain);
    }

    SECTION("Overflow case 3")
    {
        std::vector<std::string_view> const tokens{
            "2147483647",
            "10",
            "*",
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::argument_out_of_domain);
    }

    SECTION("Overflow case 4")
    {
        std::vector<std::string_view> const tokens{
            "0",
            "2147483647",
            "-",
            "2",
            "-",
        };

        CAPTURE(tokens);

        auto const [actual_result, actual_error]{
            eval_expression(tokens.cbegin(), tokens.cend())
        };

        REQUIRE(actual_error == std::errc::argument_out_of_domain);
    }
}
