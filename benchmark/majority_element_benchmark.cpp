// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/majority_element.hpp"

TEST_CASE("Boyer-Moore majority benchmarking", "[benchmark][majority_element]")
{
    using namespace forfun::majority_element;
    ankerl::nanobench::Bench()

        .title("Boyer-Moore majority")
        .relative(true)

        .run(
            NAMEOF_RAW(majority_element<std::array<int, 64>>).c_str(),
            [] noexcept -> void {
                static constexpr std::array const elements{
                    5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
                    5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
                    5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
                    5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
                };
                using ConstIter = decltype(elements)::const_iterator;

                ConstIter const r{majority_element(elements)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
