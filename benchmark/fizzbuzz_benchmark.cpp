// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <ios>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/common/io.hpp"
#include "forfun/fizzbuzz.hpp"

TEST_CASE("Fizz buzz benchmarking", "[benchmark][fizzbuzz]")
{
    using namespace forfun::fizzbuzz;

    using Func = void(char const*, std::streamsize);

    forfun::common::io::oblivion_stream output_stream;

    ankerl::nanobench::Bench()

        .title("Fizz buzz")
        .relative(true)

        .run(
            NAMEOF_RAW(basic::fizzbuzz).c_str(),
            [&output_stream]() noexcept { basic::fizzbuzz(30, output_stream); }
        )

        .run(
            NAMEOF_RAW(optimized::fizzbuzz<Func>).c_str(),
            [&output_stream]() noexcept {
                optimized::fizzbuzz(
                    1,
                    31,
                    [&output_stream](
                        char const* const buffer, std::streamsize const size
                    ) noexcept { output_stream.write(buffer, size); }
                );
            }
        )

        ;
}
