// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/palindromic_number.hpp"

TEST_CASE("Palindromic number benchmarking", "[benchmark][palindromic_number]")
{
    using namespace forfun::palindromic_number;

    static constexpr int const palindromic_num{1234554321};
    static_assert(
        (palindromic_num >= decltype(palindromic_num){})
        and (palindromic_num <= std::numeric_limits<decltype(palindromic_num)>::max())
    );

    ankerl::nanobench::Bench()

        .title("Palindromic number")
        .relative(true)

        .run(
            NAMEOF_RAW(fast::is_palindrome<int>).c_str(),
            [] noexcept -> void {
                auto const volatile p{palindromic_num};
                auto const r{fast::is_palindrome(p)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(stl::is_palindrome).c_str(),
            [] noexcept -> void {
                auto const volatile p{palindromic_num};
                auto const r{stl::is_palindrome(p)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
