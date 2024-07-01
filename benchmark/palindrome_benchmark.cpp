// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/palindrome.hpp"
#include "forfun_c/palindrome.h"

using std::string_view_literals::operator""sv;

inline constexpr std::string_view const palindrome{
    "oooooooooooooooooooooooooooooooooooooooooooooooooo"
    "oooooooooooooooooooooooooooooooooooooooooooooooooo"sv};

TEST_CASE("Palindrome benchmarking", "[benchmark][palindrome]")
{
    using namespace forfun::palindrome;

    SECTION("case-sensitive")
    {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-sensitive)")
            .relative(true)

            .run(
                NAMEOF_RAW(::is_palindrome).c_str(),
                []() {
                    auto const r{::is_palindrome(
                        palindrome.data(), palindrome.length())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::is_palindrome<char>).c_str(),
                []() {
                    auto const r{functional::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::bloated::is_palindrome<char>).c_str(),
                []() {
                    auto const r{
                        functional::bloated::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(iterator_based::is_palindrome<char>).c_str(),
                []() {
                    auto const r{iterator_based::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome<char>).c_str(),
                []() {
                    auto const r{raw::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }

    SECTION("case-insensitive")
    {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-insensitive)")
            .relative(true)

            .run(
                NAMEOF_RAW(::is_palindrome_ci).c_str(),
                []() {
                    auto const r{::is_palindrome_ci(
                        palindrome.data(), palindrome.length())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::bloated::is_palindrome_ci).c_str(),
                []() {
                    auto const r{
                        functional::bloated::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(iterator_based::is_palindrome_ci).c_str(),
                []() {
                    auto const r{iterator_based::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome_ci).c_str(),
                []() {
                    auto const r{raw::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }
}
