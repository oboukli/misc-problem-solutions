// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <forward_list>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/add_two_numbers.hpp"

TEST_CASE("Add two numbers benchmarking", "[benchmark][add_two_numbers]")
{
    using namespace forfun::add_two_numbers;

    std::forward_list<unsigned> const addend_a{1U, 4U, 5U, 6U, 5U, 2U};
    std::forward_list<unsigned> const addend_b{1U, 9U, 9U, 7U, 9U, 9U};

    std::forward_list<std::forward_list<unsigned>> results_stl{};

    ankerl::nanobench::Bench()

        .title("Add two numbers")
        .relative(true)

        .run(
            NAMEOF_RAW(stl::add_two_numbers).c_str(),
            [&addend_a, &addend_b, &results_stl]() noexcept(false) {
                auto r{stl::add_two_numbers(addend_a, addend_b)};

                results_stl.push_front(std::move(r));
            }
        )

        ;

        ankerl::nanobench::doNotOptimizeAway(results_stl);
}
