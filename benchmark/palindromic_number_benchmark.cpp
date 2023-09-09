// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/palindromic_number.hpp"

inline constexpr int const p{1234554321};

TEST_CASE("palindromic_number benchmarking", "[benchmark][palindromic_number]")
{
    static_assert(p >= 0 && p <= std::numeric_limits<decltype(p)>::max());

    ankerl::nanobench::Bench()

        .title("Palindromic number")

        .run(
            NAMEOF_RAW(forfun::palindromic_number::fast::is_palindrome<int>)
                .c_str(),
            []() {
                auto r{forfun::palindromic_number::fast::is_palindrome(p)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(forfun::palindromic_number::stl::is_palindrome).c_str(),
            []() {
                auto r{forfun::palindromic_number::stl::is_palindrome(p)};
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
