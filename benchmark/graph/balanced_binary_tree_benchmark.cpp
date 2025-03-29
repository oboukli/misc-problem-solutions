// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/graph/balanced_binary_tree.hpp"

TEST_CASE(
    "Balanced binary tree benchmarking", "[benchmark][balanced_binary_tree]"
)
{
    using namespace forfun::graph::balanced_binary_tree;

    // As seen in graph 4 in graph docs.
    binary_tree_node h_r_r_l_{12};
    binary_tree_node h_r_l_l{8};
    binary_tree_node h_r_l_r{9};
    binary_tree_node h_r_r_l{10, &h_r_r_l_, nullptr};
    binary_tree_node h_r_r_r{11};
    binary_tree_node h_l_l{4};
    binary_tree_node h_l_r{5};
    binary_tree_node h_r_l{6, &h_r_l_l, &h_r_l_r};
    binary_tree_node h_r_r{7, &h_r_r_l, &h_r_r_r};
    binary_tree_node h_l{2, &h_l_l, &h_l_r};
    binary_tree_node h_r{3, &h_r_l, &h_r_r};
    binary_tree_node const root{1, &h_l, &h_r};

    ankerl::nanobench::Bench()

        .title("Balanced binary tree")
        .relative(true)

        .run(
            NAMEOF_RAW(stl_pair::is_balanced).c_str(),
            [&root]() noexcept {
                auto const volatile r{stl_pair::is_balanced(&root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(stl_abs::is_balanced).c_str(),
            [&root]() noexcept {
                auto const volatile r{stl_abs::is_balanced(&root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(raw::is_balanced).c_str(),
            [&root]() noexcept {
                auto const volatile r{raw::is_balanced(&root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
