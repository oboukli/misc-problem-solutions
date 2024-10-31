// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <ostream>
#include <streambuf>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/fizzbuzz.hpp"

// Adapted from https://stackoverflow.com/a/11826666
class oblivion_stream final : public std::ostream {
public:
    oblivion_stream() noexcept : std::ostream(&os_buffer_)
    {
    }

private:
    class oblivion_stream_buffer_ final : public std::streambuf {
    protected:
        [[nodiscard]] auto overflow(int_type ch) noexcept -> int_type override
        {
            return ch;
        }
    };

    oblivion_stream_buffer_ os_buffer_{};
};

TEST_CASE("Fizz buzz benchmarking", "[benchmark][fizzbuzz]")
{
    using namespace forfun::fizzbuzz;

    oblivion_stream output_stream;

    ankerl::nanobench::Bench()

        .title("Fizz buzz")
        .relative(true)

        .run(
            NAMEOF_RAW(fizzbuzz).c_str(),
            [&output_stream]() noexcept { fizzbuzz(30, output_stream); }
        )

        ;
}
