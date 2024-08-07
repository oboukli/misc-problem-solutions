// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include <forfun/primality.hpp>

TEST_CASE("Primality benchmarking", "[benchmark][primality]")
{
    using namespace forfun::primality;

    ankerl::nanobench::Bench()

        .title("Primality")
        .relative(true)

        .run(
            NAMEOF_RAW(is_prime<unsigned>).c_str(),
            []() {
                bool r{is_prime(2'147'483'647U)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
