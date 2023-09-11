// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

inline constexpr int const f{514229};
inline constexpr std::uint_fast32_t const uf{f};

static_assert(uf == f);

TEST_CASE(
    "fibonacci sequence loops benchmarking", "[benchmark][fibonacci_sequence]")
{
    using result_t = std::size_t;

    ankerl::nanobench::Bench()
        .title("Fibonacci sequence loops")

        .run(
            "Three variables",
            []() {
                result_t r{};
                // clang-format off
                for (auto i{0}, j{1}, tmp{0};
                    i <= f;
                    tmp = j + i, i = j, j = tmp)
                {
                    r += i;
                }
                // clang-format on
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            "Two variables",
            []() {
                result_t r{};
                for (auto i{0}, j{1}; i <= f; j += i, i = j - i)
                {
                    r += i;
                }
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            "Two unsigned variables",
            []() {
                result_t r{};
                for (std::uint_fast32_t i{0}, j{1}; i <= uf; j += i, i = j - i)
                {
                    r += i;
                }
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            "Two variables by Creel",
            []() {
                result_t r{};
                // Source: https://youtu.be/IZc4Odd3K2Q?t=949
                for (auto i{0}, j{1}; i <= f; j = (i += j) - j)
                {
                    r += i;
                }
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
