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
    requires std::integral<T> && (sizeof(T) <= sizeof(TState))
void dummy_callback(T const n, TState* const state) noexcept
{
    *state += n;
}

TEST_CASE("fibonacci::sequence benchmarking", "[benchmark][fibonacci_sequence]")
{
    using namespace forfun::fibonacci::sequence;

    ankerl::nanobench::Bench()
        .title("forfun::fibonacci::sequence")
        .relative(true)

        .run(
            NAMEOF_RAW(slow::fib_seq<int, int>).c_str(),
            []() {
                int r{0};
                slow::fib_seq(f, dummy_callback, &r);

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(fast::fib_seq<int, int>).c_str(),
            []() {
                int r{0};
                fast::fib_seq(f, dummy_callback, &r);

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(fast::fib_seq<std::uint_fast32_t, std::uint_fast32_t>)
                .c_str(),
            []() {
                std::uint_fast32_t r{0};
                fast::fib_seq(std::uint_fast32_t{f}, dummy_callback, &r);

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        .run(
            NAMEOF_RAW(creel::fib_seq<int, int>).c_str(),
            []() {
                int r{0};
                creel::fib_seq(f, dummy_callback, &r);

                ankerl::nanobench::doNotOptimizeAway(r);
            })

        ;
}
