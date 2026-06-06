// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/permutation_in_string.hpp"

TEST_CASE(
    "Permutation in string benchmarking", "[benchmark][permutation_in_string]"
)
{
    using namespace forfun::permutation_in_string;

    static constexpr std::string_view const needle{"cdeo"};
    static constexpr std::string_view const haystack{
        "abcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstcode"
    };

    ankerl::nanobench::Bench()

        .title("Permutation in string")
        .relative(true)

        .run(
            NAMEOF_RAW(check_inclusion).c_str(),
            [] noexcept -> void {
                auto const volatile r{check_inclusion(needle, haystack)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(experimental::check_inclusion).c_str(),
            [] noexcept -> void {
                auto const volatile r{
                    experimental::check_inclusion(needle, haystack)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
