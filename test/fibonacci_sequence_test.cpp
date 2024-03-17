// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/fibonacci_sequence.hpp"

namespace {

constexpr auto const dummy_callback
    = [](int const n, std::vector<int>& state) noexcept { state.push_back(n); };

} // namespace

using namespace forfun::fibonacci::sequence;

TEMPLATE_TEST_CASE_SIG(
    "fibonacci_sequence",
    "[fibonacci_sequence]",
    ((auto fib_seq), fib_seq),
    (slow::fib_seq<int, std::vector<int>, decltype((dummy_callback))>),
    (fast::fib_seq<int, std::vector<int>, decltype((dummy_callback))>),
    (creel::fib_seq<int, std::vector<int>, decltype((dummy_callback))>))
{
    SECTION("Valid input")
    {
        GIVEN("a positive integer (incl. zero) as an upper bound")
        {
            auto const [max, expected_seq]{
                GENERATE(table<int, std::vector<int>>({
                    {0, {0}},
                    {1, {0, 1, 1}},
                    {13, {0, 1, 1, 2, 3, 5, 8, 13}},
                    {239, {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233}},
                }))};

            CAPTURE(max);

            WHEN("generating a Fibonacci sequence from zero")
            {
                std::vector<int> seq;
                seq.reserve(expected_seq.size());

                fib_seq(max, dummy_callback, seq);

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
            auto const [max]{GENERATE(table<int>({
                {-13},
                {-1},
            }))};

            CAPTURE(max);

            WHEN("generating a Fibonacci sequence from zero")
            {
                std::vector<int> seq;

                fib_seq(max, dummy_callback, seq);

                THEN("sequence is empty")
                {
                    REQUIRE(seq == std::vector<int>{});
                }
            }
        }
    }
}
