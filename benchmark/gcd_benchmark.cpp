// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/gcd.hpp"

TEST_CASE("Greatest common divisor benchmarking", "[benchmark][gcd]")
{
    using namespace forfun::gcd::euclid;

    ankerl::nanobench::Bench()

        .title("Greatest common divisor")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::gcd).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(iterative::gcd(a, b));
            }
        )

        .run(
            NAMEOF_RAW(iterative::gcd_p).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(iterative::gcd_p(a, b));
            }
        )

        .run(
            NAMEOF_RAW(recursive::gcd).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(recursive::gcd(a, b));
            }
        )

        .run(
            NAMEOF_RAW(recursive::gcd_p).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(recursive::gcd_p(a, b));
            }
        )

        .run(
            NAMEOF_RAW(subtraction_based::gcd).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(
                    subtraction_based::gcd(a, b)
                );
            }
        )

        .run(
            NAMEOF_RAW(subtraction_based::gcd_p).c_str(),
            [] noexcept -> void {
                int const volatile a{1U << 25U};
                int const volatile b{(1U << 15U) * 59'049};
                ankerl::nanobench::doNotOptimizeAway(
                    subtraction_based::gcd_p(a, b)
                );
            }
        )

        ;
}
