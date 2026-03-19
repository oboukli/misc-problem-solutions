// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <tuple>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include "forfun/container/min_stack.hpp"

TEST_CASE("Min stack benchmarking", "[benchmark][min_stack]")
{
    using namespace forfun::container::min_stack;

    ankerl::nanobench::Bench()

        .title("Min stack")
        .relative(true)

        .run(
            "double_buffered::min_stack",
            [] noexcept -> void {
                double_buffered::min_stack stack{};

                stack.push(16);
                stack.push(15);
                stack.push(14);
                stack.push(13);

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.push(-9);
                stack.push(-9);
                stack.push(-9);
                stack.push(-9);

                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.push(8);
                stack.push(7);
                stack.push(6);
                stack.push(5);

                stack.push(4);
                stack.push(3);
                stack.push(2);
                stack.push(1);

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();

                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.empty();

                ankerl::nanobench::doNotOptimizeAway(&stack);
            }
        )

        .run(
            "cache_friendly::min_stack",
            [] noexcept -> void {
                cache_friendly::min_stack stack{};

                stack.push(16);
                stack.push(15);
                stack.push(14);
                stack.push(13);

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.push(-9);
                stack.push(-9);
                stack.push(-9);
                stack.push(-9);

                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.push(8);
                stack.push(7);
                stack.push(6);
                stack.push(5);

                stack.push(4);
                stack.push(3);
                stack.push(2);
                stack.push(1);

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();
                std::ignore = stack.size();

                stack.pop();
                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.min();
                std::ignore = stack.top();

                stack.pop();
                stack.pop();
                stack.pop();

                std::ignore = stack.empty();

                ankerl::nanobench::doNotOptimizeAway(&stack);
            }
        )

        ;
}
