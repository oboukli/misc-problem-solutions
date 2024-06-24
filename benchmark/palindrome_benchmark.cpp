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
                    auto const r{
                        ::is_palindrome(palindrome.data(), palindrome.size())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(fast::is_palindrome).c_str(),
                []() {
                    auto const r{fast::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome).c_str(),
                []() {
                    auto const r{raw::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(stl_fast::is_palindrome).c_str(),
                []() {
                    auto const r{stl_fast::is_palindrome(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(stl_bloated::is_palindrome).c_str(),
                []() {
                    auto const r{stl_bloated::is_palindrome(palindrome)};

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
                        palindrome.data(), palindrome.size())};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(fast::is_palindrome_ci).c_str(),
                []() {
                    auto const r{fast::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(raw::is_palindrome_ci).c_str(),
                []() {
                    auto const r{raw::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(stl_bloated::is_palindrome_ci).c_str(),
                []() {
                    auto const r{stl_bloated::is_palindrome_ci(palindrome)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }
}
