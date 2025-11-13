// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/common/concepts.hpp"
#include "forfun/fibonacci_sequence.hpp"

namespace {

template <forfun::common::concepts::addition_unpromoted T>
auto dummy_callback(T const n, T& state) noexcept -> void
{
    state += n;
}

} // namespace

TEST_CASE("Fibonacci sequence benchmarking", "[benchmark][fibonacci_sequence]")
{
    using namespace forfun::fibonacci::sequence;

    using fn_int_t = decltype(dummy_callback<int>);
    using fn_fast_t = decltype(dummy_callback<std::uint_fast32_t>);

    ankerl::nanobench::Bench()
        .title("Fibonacci sequence")
        .relative(true)

        .run(
            NAMEOF_RAW(slow::fib_seq<int, int, fn_int_t>).c_str(),
            [] noexcept -> void {
                int const volatile f{514'229};
                int r{};
                slow::fib_seq<int, int, fn_int_t>(f, dummy_callback, r);

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(fast::fib_seq<int, int, fn_int_t>).c_str(),
            [] noexcept -> void {
                int const volatile f{514'229};
                int r{};
                fast::fib_seq<int, int, fn_int_t>(f, dummy_callback, r);

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                fast::fib_seq<std::uint_fast32_t, std::uint_fast32_t, fn_fast_t>
            )
                .c_str(),
            [] noexcept -> void {
                uint_fast32_t const volatile f{514'229};
                std::uint_fast32_t r{};
                fast::
                    fib_seq<std::uint_fast32_t, std::uint_fast32_t, fn_fast_t>(
                        f, dummy_callback, r
                    );

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(creel::fib_seq<int, int, fn_int_t>).c_str(),
            [] noexcept -> void {
                int const volatile f{514'229};
                int r{};
                creel::fib_seq<int, int, fn_int_t>(f, dummy_callback, r);

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
