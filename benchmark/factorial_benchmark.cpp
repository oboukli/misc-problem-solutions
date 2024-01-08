// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/factorial.hpp"

TEST_CASE("factorial benchmarking", "[benchmark][factorial]")
{
    namespace iterative = forfun::factorial::iterative;
#if FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE
    namespace stl_functional = forfun::factorial::stl_functional;
#endif // FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE

    ankerl::nanobench::Bench()

        .title("forfun::factorial")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::factorial<std::uint64_t>).c_str(),
            []() {
                auto const volatile n{std::uint64_t{20}};
                auto const r{iterative::factorial(n)};

                assert(r == std::uint64_t{2'432'902'008'176'640'000});

                ankerl::nanobench::doNotOptimizeAway(r);
            })

#if FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE
        .run(
            NAMEOF_RAW(stl_functional::factorial<std::uint64_t>).c_str(),
            []() {
                auto const volatile n{std::uint64_t{20}};
                auto const r{forfun::factorial::stl_functional::factorial(n)};

                assert(r == std::uint64_t{2'432'902'008'176'640'000});

                ankerl::nanobench::doNotOptimizeAway(r);
            })
#endif // FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE

        ;
}
