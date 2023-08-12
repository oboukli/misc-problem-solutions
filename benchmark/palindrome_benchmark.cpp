// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/palindrome.h"
#include "forfun/palindrome.hpp"

TEST_CASE("forfun::palindrome benchmarking", "[benchmark][palindrome]") {
    constexpr std::string_view const palindrome{
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"};

    SECTION("case-sensitive") {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-sensitive)")

            .run(
                NAMEOF_RAW(::is_palindrome).c_str(),
                [&palindrome]() {
                    auto r{
                        ::is_palindrome(palindrome.data(), palindrome.size())};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::fast::is_palindrome).c_str(),
                [&palindrome]() {
                    auto r{forfun::palindrome::fast::is_palindrome(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::raw::is_palindrome).c_str(),
                [&palindrome]() {
                    auto r{forfun::palindrome::raw::is_palindrome(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::stl_fast::is_palindrome).c_str(),
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_fast::is_palindrome(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::stl_bloated::is_palindrome)
                    .c_str(),
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_bloated::is_palindrome(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }

    SECTION("case-insensitive") {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-insensitive)")

            .run(
                NAMEOF_RAW(::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto r{::is_palindrome_ci(
                        palindrome.data(), palindrome.size())};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::fast::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto r{
                        forfun::palindrome::fast::is_palindrome_ci(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::raw::is_palindrome_ci).c_str(),
                [&palindrome]() {
                    auto r{
                        forfun::palindrome::raw::is_palindrome_ci(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                NAMEOF_RAW(forfun::palindrome::stl_bloated::is_palindrome_ci)
                    .c_str(),
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_bloated::is_palindrome_ci(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }
}
