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
    using namespace forfun::evaluate_reverse_polish_notation;

    using VecConstIter = std::vector<std::string_view>::const_iterator;

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

    ankerl::nanobench::Bench()

        .title("Evaluate reverse polish notation")
        .relative(true)

        .run(
            NAMEOF_RAW(hardened::eval_expression<VecConstIter, VecConstIter>)
                .c_str(),
            [&tokens] -> void {
                auto const r{
                    hardened::eval_expression(tokens.cbegin(), tokens.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(unhardened::eval_expression<VecConstIter, VecConstIter>)
                .c_str(),
            [&tokens] -> void {
                auto const r{
                    unhardened::eval_expression(tokens.cbegin(), tokens.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                speed_optimized::eval_expression<VecConstIter, VecConstIter>
            )
                .c_str(),
            [&tokens] noexcept -> void {
                auto const r{speed_optimized::eval_expression(
                    tokens.cbegin(), tokens.cend()
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
