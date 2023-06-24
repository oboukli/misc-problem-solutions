// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindrome.hpp"

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <string_view>

int main() {
    std::string_view sv{"oooooooooooooooooooooooooooooooooooooooooooooooooo"
                        "oooooooooooooooooooooooooooooooooooooooooooooooooo"};

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::raw::is_palindrome", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::raw::is_palindrome(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::fast::is_palindrome", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::fast::is_palindrome(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::stl_bloated::is_palindrome", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::stl_bloated::is_palindrome(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::stl_fast::is_palindrome", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::stl_fast::is_palindrome(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::raw::is_palindrome_ci", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::raw::is_palindrome_ci(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::fast::is_palindrome_ci", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::fast::is_palindrome_ci(sv));
        });

    ankerl::nanobench::Bench().run(
        "forfun::palindrome::stl_bloated::is_palindrome_ci", [&sv]() {
            ankerl::nanobench::doNotOptimizeAway(
                forfun::palindrome::stl_bloated::is_palindrome_ci(sv));
        });

    return 0;
}
