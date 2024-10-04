// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/fizzbuzz.hpp"

TEST_CASE("Fizz buzz benchmarking", "[benchmark][fizzbuzz]")
{
    using namespace forfun::fizzbuzz;

    ankerl::nanobench::Bench()

        .title("Fizz buzz")
        .relative(true)

        .run(
            NAMEOF_RAW(fizzbuzz).c_str(),
            []() noexcept {
                auto const volatile r{fizzbuzz(30)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
