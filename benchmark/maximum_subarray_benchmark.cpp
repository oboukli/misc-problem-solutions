// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/maximum_subarray.hpp"

TEST_CASE("Maximum subarray benchmarking", "[benchmark][maximum_subarray]")
{
    using namespace forfun::maximum_subarray;

    std::array const input{0, 52, -100, 0, 1, 30, -6, 33};
    using ConstIter = decltype(input)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Maximum subarray")
        .relative(true)

        .run(
            NAMEOF_RAW(brute_force::max_sum<ConstIter, ConstIter>).c_str(),
            [&input]() noexcept {
                auto const volatile r{
                    brute_force::max_sum(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::max_sum<ConstIter, ConstIter>).c_str(),
            [&input]() noexcept {
                auto const volatile r{
                    recursive::max_sum(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(streaming::max_sum<ConstIter, ConstIter>).c_str(),
            [&input]() noexcept {
                auto const volatile r{
                    streaming::max_sum(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
