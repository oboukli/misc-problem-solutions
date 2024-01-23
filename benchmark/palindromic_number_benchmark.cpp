// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/palindromic_number.hpp"

inline constexpr int const p{1234554321};

TEST_CASE("palindromic_number benchmarking", "[benchmark][palindromic_number]")
{
    static_assert(p >= 0 && p <= std::numeric_limits<decltype(p)>::max());

    using namespace forfun::palindromic_number;

    ankerl::nanobench::Bench()

        .title("Palindromic number")
        .relative(true)

        .run(
            NAMEOF_RAW(fast::is_palindrome<int>).c_str(),
            []() {
                auto r{forfun::palindromic_number::fast::is_palindrome(p)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(stl::is_palindrome).c_str(),
            []() {
                auto r{forfun::palindromic_number::stl::is_palindrome(p)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
