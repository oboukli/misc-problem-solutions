// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <limits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/hamming_weight.hpp"

TEST_CASE("hamming_weight benchmarking", "[benchmark][hamming_weight]")
{
    using namespace forfun::hamming_weight;

    std::size_t const volatile num{
        (1UZ << std::size_t{std::numeric_limits<std::size_t>::digits - 1}) | 1UZ
    };

    ankerl::nanobench::Bench()

        .title("Humming weight")
        .relative(true)

        .run(
            NAMEOF_RAW(linear_functional::get_hamming_weight).c_str(),
            [&num]() noexcept {
                auto const volatile r{
                    linear_functional::get_hamming_weight(num)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(linear_imperative::get_hamming_weight).c_str(),
            [&num]() noexcept {
                auto const volatile r{
                    linear_imperative::get_hamming_weight(num)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(optimized_imperative::get_hamming_weight).c_str(),
            [&num]() noexcept {
                auto const volatile r{
                    optimized_imperative::get_hamming_weight(num)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
