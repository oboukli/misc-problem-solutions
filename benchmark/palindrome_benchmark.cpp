// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <string_view>

#include "forfun/palindrome.hpp"

int main() {
    constexpr std::string_view const palindrome{
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"
        "oooooooooooooooooooooooooooooooooooooooooooooooooo"};

    {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-sensitive)")

            .run(
                "forfun::palindrome::fast::is_palindrome",
                [&palindrome]() {
                    auto r{forfun::palindrome::fast::is_palindrome(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                "forfun::palindrome::raw::is_palindrome",
                [&palindrome]() {
                    auto r{forfun::palindrome::raw::is_palindrome(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                "forfun::palindrome::stl_fast::is_palindrome",
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_fast::is_palindrome(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                "forfun::palindrome::stl_bloated::is_palindrome",
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_bloated::is_palindrome(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }

    {
        ankerl::nanobench::Bench()

            .title("Palindrome (case-insensitive)")

            .run(
                "forfun::palindrome::fast::is_palindrome_ci",
                [&palindrome]() {
                    auto r{
                        forfun::palindrome::fast::is_palindrome_ci(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                "forfun::palindrome::raw::is_palindrome_ci",
                [&palindrome]() {
                    auto r{
                        forfun::palindrome::raw::is_palindrome_ci(palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            .run(
                "forfun::palindrome::stl_bloated::is_palindrome_ci",
                [&palindrome]() {
                    auto r{forfun::palindrome::stl_bloated::is_palindrome_ci(
                        palindrome)};
                    ankerl::nanobench::doNotOptimizeAway(r);
                })

            ;
    }
}
