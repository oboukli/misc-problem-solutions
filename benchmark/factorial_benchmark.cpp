// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/factorial.hpp"

TEST_CASE("Factorial benchmarking", "[benchmark][factorial]")
{
    using namespace forfun::factorial;

    ankerl::nanobench::Bench()

        .title("Factorial")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::factorial<std::uint64_t>).c_str(),
            [] noexcept -> void {
                auto const volatile n{std::uint64_t{20U}};
                auto const r{iterative::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::factorial<std::uint64_t>).c_str(),
            [] noexcept -> void {
                auto const volatile n{std::uint64_t{20U}};
                auto const r{recursive::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(stl_functional::factorial<std::uint64_t>).c_str(),
            [] noexcept -> void {
                auto const volatile n{std::uint64_t{20U}};
                auto const r{stl_functional::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
