// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/fibonacci_sequence.hpp"

namespace {

constexpr auto const dummy_noexcept_lambda
    = [](int const n, std::vector<int>& state) noexcept { state.push_back(n); };

// clang-format off
constexpr auto const dummy_throwing_lambda
    = []([[maybe_unused]] int const n,
        [[maybe_unused]] std::vector<int>& state) noexcept(false) {};
// clang-format on

void dummy_noexcept_func() noexcept
{
}

void dummy_throwing_func() noexcept(false)
{
}

} // namespace

using namespace forfun::fibonacci::sequence;

TEMPLATE_TEST_CASE_SIG(
    "fibonacci_sequence",
    "[fibonacci_sequence]",
    ((auto fib_seq), fib_seq),
    (slow::fib_seq<int, std::vector<int>, decltype((dummy_noexcept_lambda))>),
    (fast::fib_seq<int, std::vector<int>, decltype((dummy_noexcept_lambda))>),
    (creel::fib_seq<int, std::vector<int>, decltype((dummy_noexcept_lambda))>))
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

                fib_seq(max, dummy_noexcept_lambda, seq);

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

                fib_seq(max, dummy_noexcept_lambda, seq);

                THEN("sequence is empty")
                {
                    REQUIRE(seq == std::vector<int>{});
                }
            }
        }
    }
}

TEST_CASE("fibonacci_sequence noexcept_callable", "[fibonacci_sequence]")
{
    SECTION("Positive")
    {
        // clang-format off
        STATIC_REQUIRE(
            noexcept_callable<decltype(dummy_noexcept_lambda), int, std::vector<int>&>);
        STATIC_REQUIRE(
            noexcept_callable<decltype(dummy_noexcept_func)>);

        STATIC_REQUIRE(
            noexcept_callable<decltype([](int, int) noexcept {}), int, int>);
        STATIC_REQUIRE(
            noexcept_callable<decltype([](char, int) noexcept {}), int, char>);

        STATIC_REQUIRE(
            noexcept_callable<decltype([](int, char*) noexcept {}), double, char*>);

        STATIC_REQUIRE(
            noexcept_callable<decltype([](int, std::string) noexcept {}), int, std::string>);
        STATIC_REQUIRE(
            noexcept_callable<decltype([](int, std::string&) noexcept {}), int, std::string&>);

        STATIC_REQUIRE(
            noexcept_callable<decltype([]() noexcept {})>);
        STATIC_REQUIRE(
            noexcept_callable<decltype([](int) noexcept {}), int>);
        STATIC_REQUIRE(
            noexcept_callable<decltype([](int, char, double, std::string) noexcept {}), int, int, int, std::string>);
        // clang-format on
    }

    SECTION("Negative")
    {
        SECTION("noexcept is false")
        {
            // clang-format off
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_throwing_lambda), int, std::vector<int>&>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_throwing_func)>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int, int) {}), int, int>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int, int) noexcept(false) {}), int, int>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int, std::string&) {}), int, std::string&>);
            // clang-format on
        }

        SECTION("Parameter type mismatch")
        {
            // clang-format off
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_noexcept_lambda), int, std::vector<int>>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_noexcept_lambda), int, std::vector<char>&>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int, int&) noexcept {}), int, int>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](char, char&) noexcept {}), int, int&>);
            // clang-format on
        }

        SECTION("Parameter list mismatch")
        {
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_noexcept_lambda), int, int&>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype(dummy_noexcept_lambda)>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([]() noexcept {}), int, int>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int) noexcept {}), int, int>);
            STATIC_REQUIRE_FALSE(
                noexcept_callable<decltype([](int, int) noexcept {})>);
        }
    }
}
