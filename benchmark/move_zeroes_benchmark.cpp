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
    using namespace forfun::move_zeroes;

    using ContainerType = std::array<int, 128>;
    using Itr = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("move_zeroes")
        .relative(true)

        .run(
            NAMEOF_RAW(sol1::move_zeroes<Itr>).c_str(),
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
                static_assert(nums.size() == std::tuple_size_v<ContainerType>);

                sol1::move_zeroes(nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            })

        .run(
            NAMEOF_RAW(sol2::move_zeroes<Itr>).c_str(),
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
                static_assert(nums.size() == std::tuple_size_v<ContainerType>);

                sol2::move_zeroes(nums.begin(), nums.end());

                ankerl::nanobench::doNotOptimizeAway(nums);
            })

        .run(NAMEOF_RAW(stl::move_zeroes<Itr>).c_str(), []() {
            std::array nums{
                0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0,
                0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0, 1, 0, 3,  12, 0,
                1, 0, 3, 12, 0,  1, 0, 3, 12, 0,  1, 0, 3, 12, 1,  0};
            static_assert(nums.size() == std::tuple_size_v<ContainerType>);

            stl::move_zeroes(nums.begin(), nums.end());

            ankerl::nanobench::doNotOptimizeAway(nums);
        });
}
