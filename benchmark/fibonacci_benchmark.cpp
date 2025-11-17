// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/fibonacci.hpp"

TEST_CASE("Fibonacci number benchmarking", "[benchmark][fibonacci]")
{
    using namespace forfun::fibonacci;

    ankerl::nanobench::Bench()

        .title("Fibonacci number")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::fib<std::uint_fast32_t>).c_str(),
            [] noexcept -> void {
                std::uint_fast32_t const volatile n{7U};

                auto const r{iterative::fib(n)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::fib<std::uint_fast32_t>).c_str(),
            [] noexcept -> void {
                std::uint_fast32_t const volatile n{7U};

                auto const r{recursive::fib(n)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
