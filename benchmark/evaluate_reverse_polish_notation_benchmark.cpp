// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/evaluate_reverse_polish_notation.hpp"

TEST_CASE(
    "Evaluate reverse polish notation benchmarking",
    "[benchmark][evaluate_reverse_polish_notation]"
)
{
    using std::string_view_literals::operator""sv;

    using namespace forfun::evaluate_reverse_polish_notation;

    using VecConstIter = std::vector<std::string_view>::const_iterator;

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

    ankerl::nanobench::Bench()

        .title("Evaluate reverse polish notation")
        .relative(true)

        .run(
            NAMEOF_RAW(hardened::eval_expression<VecConstIter, VecConstIter>)
                .c_str(),
            [&tokens]() {
                auto const r{
                    hardened::eval_expression(tokens.cbegin(), tokens.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(unhardened::eval_expression<VecConstIter, VecConstIter>)
                .c_str(),
            [&tokens]() {
                auto const r{
                    unhardened::eval_expression(tokens.cbegin(), tokens.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(
                speed_optimized::eval_expression<VecConstIter, VecConstIter>
            )
                .c_str(),
            [&tokens]() noexcept {
// Ignore Division by zero [core.DivideZero] warning.
#ifndef __clang_analyzer__
                auto const r{speed_optimized::eval_expression(
                    tokens.cbegin(), tokens.cend()
                )};
                ankerl::nanobench::doNotOptimizeAway(r);
#endif // __clang_analyzer__
            }
        )

        ;
}
