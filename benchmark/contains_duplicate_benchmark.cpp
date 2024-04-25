// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("contains_duplicate benchmarking", "[benchmark][contains_duplicate]")
{
    using namespace forfun::contains_duplicate;

    using ContainerType = std::array<int, 32>;
    using Itr = ContainerType::iterator;

    constexpr std::array const superprimes{
        3,   5,   11,  17,  31,  41,  59,  67,  83,  109, 127,
        157, 179, 191, 211, 241, 277, 283, 331, 353, 367, 401,
        431, 461, 509, 547, 563, 587, 599, 617, 709, 739,
    };

    static_assert(superprimes.size() == std::tuple_size<ContainerType>::value);

    ankerl::nanobench::Bench()

        .title("forfun::contains_duplicate")
        .relative(true)

        .run(
            NAMEOF_RAW(contains_duplicate<Itr>).c_str(),
            [&superprimes]() {
                ankerl::nanobench::doNotOptimizeAway(contains_duplicate(
                    superprimes.cbegin(), superprimes.cend()));
            })

        ;
}
