// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <forward_list>
#include <memory>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/add_two_numbers.hpp"

#include "forfun_c/add_two_numbers.h"
#include "forfun_c/container/forward_list.h"

TEST_CASE("Add two numbers benchmarking", "[benchmark][add_two_numbers]")
{
    using namespace forfun::add_two_numbers;

    std::forward_list<unsigned> const addend_a{1U, 4U, 5U, 6U, 5U, 2U};
    std::forward_list<unsigned> const addend_b{1U, 9U, 9U, 7U, 9U, 9U};
    std::forward_list<std::forward_list<unsigned>> results_stl{};

    ::forfun_forward_list_node node_a_5 = {.next = nullptr, .value = 2U};
    ::forfun_forward_list_node node_a_4 = {.next = &node_a_5, .value = 5U};
    ::forfun_forward_list_node node_a_3 = {.next = &node_a_4, .value = 6U};
    ::forfun_forward_list_node node_a_2 = {.next = &node_a_3, .value = 5U};
    ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 4U};
    ::forfun_forward_list_node const node_a_0
        = {.next = &node_a_1, .value = 1U};

    ::forfun_forward_list_node node_b_5 = {.next = nullptr, .value = 9U};
    ::forfun_forward_list_node node_b_4 = {.next = &node_b_5, .value = 9U};
    ::forfun_forward_list_node node_b_3 = {.next = &node_b_4, .value = 7U};
    ::forfun_forward_list_node node_b_2 = {.next = &node_b_3, .value = 9U};
    ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 9U};
    ::forfun_forward_list_node const node_b_0
        = {.next = &node_b_1, .value = 1U};

    ::forfun_forward_list_node const* const node_a{&node_a_0};
    ::forfun_forward_list_node const* const node_b{&node_b_0};

    std::forward_list<std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>>
        results_c_iterative{};

    std::forward_list<std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>>
        results_c_recursive{};

    ankerl::nanobench::Bench()

        .title("Add two numbers")
        .relative(true)

        .run(
            NAMEOF_RAW(::forfun_iterative_add_two_numbers).c_str(),
            [node_a, node_b, &results_c_iterative]() noexcept {
                auto* r{::forfun_iterative_add_two_numbers(node_a, node_b)};

                results_c_iterative.emplace_front(r, &::forfun_free_node_list);
            }
        )

        .run(
            NAMEOF_RAW(::forfun_recursive_add_two_numbers).c_str(),
            [node_a, node_b, &results_c_recursive]() noexcept {
                auto* r{::forfun_recursive_add_two_numbers(node_a, node_b)};

                results_c_recursive.emplace_front(r, &::forfun_free_node_list);
            }
        )

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
