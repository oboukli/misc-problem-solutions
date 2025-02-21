// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/longest_consecutive_sequence.hpp"

TEST_CASE(
    "Longest consecutive sequence benchmarking",
    "[benchmark][longest_consecutive_sequence]"
)
{
    using namespace forfun;

    using Iter = std::vector<int>::iterator;

    ankerl::nanobench::Bench()

        .title("Longest consecutive sequence")
        .relative(true)

        .run(
            NAMEOF_RAW(
                longest_consecutive_sequence::counted::
                    longest_consecutive<Iter, Iter>
            )
                .c_str(),
            []() noexcept {
                std::vector nums{
                    // clang-format off
                    1,  1,   2,   3,   44,  45,  46,  47,
                    47, 47,  47,  48,  7,   8,   9,   10,
                    11, 173, 179, 181, 191, 193, 197, 199,
                    22, 23,  24,  211, 283, 293, 307, 311,
                    // clang format on
                };

                auto const volatile r{
                    forfun::longest_consecutive_sequence::counted::
                        longest_consecutive(nums.begin(), nums.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                longest_consecutive_sequence::measured::
                    longest_consecutive<Iter, Iter>
            )
                .c_str(),
            []() noexcept {
                std::vector nums{
                    // clang-format off
                    1,  1,   2,   3,   44,  45,  46,  47,
                    47, 47,  47,  48,  7,   8,   9,   10,
                    11, 173, 179, 181, 191, 193, 197, 199,
                    22, 23,  24,  211, 283, 293, 307, 311,
                    // clang format on
                };

                auto const volatile r{
                    forfun::longest_consecutive_sequence::measured::
                        longest_consecutive(nums.begin(), nums.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                longest_consecutive_sequence::set_scanning::
                    longest_consecutive<Iter, Iter>
            )
                .c_str(),
            []() noexcept {
                std::vector nums{
                    // clang-format off
                    1,  1,   2,   3,   44,  45,  46,  47,
                    47, 47,  47,  48,  7,   8,   9,   10,
                    11, 173, 179, 181, 191, 193, 197, 199,
                    22, 23,  24,  211, 283, 293, 307, 311,
                    // clang format on
                };

                auto const volatile r{
                    forfun::longest_consecutive_sequence::set_scanning::
                        longest_consecutive(nums.begin(), nums.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                longest_consecutive_sequence::set_sliding::
                    longest_consecutive<Iter, Iter>
            )
                .c_str(),
            []() noexcept {
                std::vector nums{
                    // clang-format off
                    1,  1,   2,   3,   44,  45,  46,  47,
                    47, 47,  47,  48,  7,   8,   9,   10,
                    11, 173, 179, 181, 191, 193, 197, 199,
                    22, 23,  24,  211, 283, 293, 307, 311,
                    // clang format on
                };

                auto const volatile r{
                    forfun::longest_consecutive_sequence::set_sliding::
                        longest_consecutive(nums.begin(), nums.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
