// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/move_zeroes.hpp"

TEST_CASE("move_zeroes benchmarking", "[benchmark][move_zeroes]")
{
    using It = std::array<int, 128>::iterator;

    ankerl::nanobench::Bench()

        .title("move_zeroes")
        .relative(true)

        .run(
            NAMEOF_RAW(forfun::move_zeroes::sol1::move_zeroes<It>).c_str(),
            []() {
                std::array nums{
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0};

                forfun::move_zeroes::sol1::move_zeroes(
                    nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            })

        .run(
            NAMEOF_RAW(forfun::move_zeroes::sol2::move_zeroes<It>).c_str(),
            []() {
                std::array nums{
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0};

                forfun::move_zeroes::sol2::move_zeroes(
                    nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            })

        .run(
            NAMEOF_RAW(forfun::move_zeroes::stl::move_zeroes<It>).c_str(),
            []() {
                std::array nums{
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                    0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                    1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0};

                forfun::move_zeroes::stl::move_zeroes(nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            });
}
