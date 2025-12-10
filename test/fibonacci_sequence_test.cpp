// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/fibonacci_sequence.hpp"

namespace {

constexpr auto const record_state{
    [](int const n, std::vector<int>& state) -> void { state.push_back(n); }
};

using namespace forfun::fibonacci::sequence;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Fibonacci sequence",
    "[fibonacci_sequence]",
    (auto fib_seq, fib_seq),
    (slow::fib_seq<int, std::vector<int>, decltype(record_state)>),
    (fast::fib_seq<int, std::vector<int>, decltype(record_state)>),
    (creel::fib_seq<int, std::vector<int>, decltype(record_state)>)
)
{
    SECTION("Valid input")
    {
        GIVEN("a positive integer (incl. zero) as an upper bound")
        {
            auto const [max, expected_seq]{GENERATE(
                table<int, std::vector<int>>({
                    {0, {0}},
                    {1, {0, 1, 1}},
                    {13, {0, 1, 1, 2, 3, 5, 8, 13}},
                    {239, {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233}},
                })
            )};

            CAPTURE(max);

            WHEN("generating a Fibonacci sequence from zero")
            {
                std::vector<int> seq;
                seq.reserve(expected_seq.size());

                fib_seq(max, record_state, seq);

                THEN("sequence is valid")
                {
                    REQUIRE(seq == expected_seq);
                }
            }
        }
    }

    SECTION("Negative input")
    {
        GIVEN("a negative integer as an upper bound")
        {
            auto const [max]{GENERATE(
                table<int>({
                    {-13},
                    {-1},
                })
            )};

            CAPTURE(max);

            WHEN("generating a Fibonacci sequence from zero")
            {
                std::vector<int> seq;

                fib_seq(max, record_state, seq);

                THEN("sequence is empty")
                {
                    REQUIRE(seq.empty());
                }
            }
        }
    }
}
