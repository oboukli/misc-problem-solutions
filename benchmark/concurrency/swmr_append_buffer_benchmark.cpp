// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <new>

#include <catch2/catch_test_macros.hpp>

#include <nameof.hpp>

#include <nanobench.h>

#include <forfun/concurrency/swmr_append_buffer.hpp>

TEST_CASE("SWMR append buffer benchmarking", "[benchmark][swmr_append_buffer]")
{
    using namespace forfun::concurrency;

    static constexpr std::size_t const capacity{16};

    ankerl::nanobench::Bench()

        .title("SWMR append buffer")
        .relative(true)

        .run(
            NAMEOF_RAW(
                wait_free::swmr_append_buffer<
                    int,
                    capacity,
                    std::hardware_destructive_interference_size>{}
            )
                .c_str(),
            [] noexcept -> void {
                // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
                int volatile val /*[[indeterminate]]*/;

                wait_free::swmr_append_buffer<
                    int,
                    capacity,
                    std::hardware_destructive_interference_size>
                    queue{};

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                queue.emplace_back(502807);
                val = queue.to_span().back();

                ankerl::nanobench::doNotOptimizeAway(&val);
            }
        )

        ;
}
