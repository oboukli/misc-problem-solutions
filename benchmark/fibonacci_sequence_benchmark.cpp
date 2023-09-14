// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/fibonacci_sequence.hpp"

inline constexpr int const f{514229};

template <typename T, typename TState>
    requires std::integral<T> && (sizeof(T) < sizeof(TState))
void dummy_callback(T const n, TState* const state) noexcept
{
    *state += n;
}

TEST_CASE("fibonacci::sequence benchmarking", "[benchmark][fibonacci_sequence]")
{
    using namespace forfun::fibonacci::sequence;

    using result_t = std::size_t;

    ankerl::nanobench::Bench()
        .title("forfun::fibonacci::sequence")

        .run(
            NAMEOF_RAW(slow::fib_seq<int, result_t>).c_str(),
            []() {
                result_t r{};
                forfun::fibonacci::sequence::slow::fib_seq(
                    f, dummy_callback, &r);
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(fast::fib_seq<int, result_t>).c_str(),
            []() {
                result_t r{};
                forfun::fibonacci::sequence::fast::fib_seq(
                    f, dummy_callback, &r);
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(fast::fib_seq<std::uint_fast32_t, result_t>).c_str(),
            []() {
                result_t r{};
                forfun::fibonacci::sequence::fast::fib_seq(
                    std::uint_fast32_t{f}, dummy_callback, &r);
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(creel::fib_seq<int, result_t>).c_str(),
            []() {
                result_t r{};
                forfun::fibonacci::sequence::creel::fib_seq(
                    f, dummy_callback, &r);
                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
