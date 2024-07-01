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

TEST_CASE("Palindrome benchmarking", "[benchmark][palindrome]")
{
    using std::string_view_literals::operator""sv;

    using namespace forfun::palindrome;

    std::string_view palindrome{
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"sv};

    SECTION("case-sensitive")
    {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-sensitive)")
            .relative(true)

            .run(
                NAMEOF_RAW(::is_palindrome).c_str(),
                [&palindrome]() {
                    auto const r{::is_palindrome(
                        palindrome.data(), palindrome.length())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::is_palindrome<char>).c_str(),
                [&palindrome]() {
                    auto const r{functional::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::bloated::is_palindrome<char>).c_str(),
                [&palindrome]() {
                    auto const r{
                        functional::bloated::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(iterator_based::is_palindrome<char>).c_str(),
                [&palindrome]() {
                    auto const r{iterator_based::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome<char>).c_str(),
                [&palindrome]() {
                    auto const r{raw::is_palindrome<char>(
                        palindrome.data(), palindrome.length())};

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
                [&palindrome]() {
                    auto const r{::is_palindrome_ci(
                        palindrome.data(), palindrome.length())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(functional::bloated::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto const r{
                        functional::bloated::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(iterator_based::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto const r{iterator_based::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto const r{raw::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }
}
