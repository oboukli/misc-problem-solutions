// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/concurrency/spsc_bound_queue.hpp"

TEST_CASE(
    "Wait-free SPSC append-only bounded queue benchmarking",
    "[benchmark][spsc_bound_queue]"
)
{
    using namespace forfun::concurrency;

    static constexpr std::size_t const capacity{16};

    ankerl::nanobench::Bench()

        .title("Wait-free SPSC append-only bounded queue")
        .relative(true)

        .run(
            NAMEOF_RAW(wait_free::spsc_bound_queue<int, capacity>{}).c_str(),
            [] noexcept -> void {
                // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
                int volatile val /*[[indeterminate]]*/;

                wait_free::spsc_bound_queue<int, capacity> queue{};

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
