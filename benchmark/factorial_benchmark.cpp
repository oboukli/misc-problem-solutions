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
    // NOLINTNEXTLINE
    using namespace forfun::factorial;

    ankerl::nanobench::Bench()

        .title("forfun::factorial")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::factorial<std::uint64_t>).c_str(),
            []() {
                auto const volatile n{std::uint64_t{20}};
                auto const r{iterative::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(recursive::factorial<std::uint64_t>).c_str(),
            []() {
                auto const volatile n{std::uint64_t{20}};
                auto const r{recursive::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            })

#if FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE
        .run(
            NAMEOF_RAW(stl_functional::factorial<std::uint64_t>).c_str(),
            []() {
                auto const volatile n{std::uint64_t{20}};
                auto const r{stl_functional::factorial(n)};

                ankerl::nanobench::doNotOptimizeAway(r);
            })
#endif // FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE

        ;
}
