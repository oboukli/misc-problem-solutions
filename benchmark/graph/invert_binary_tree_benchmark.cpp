// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/graph/binary_tree_node.hpp"
#include "forfun/graph/invert_binary_tree.hpp"

TEST_CASE("Invert binary tree benchmarking", "[benchmark][invert_binary_tree]")
{
    using namespace forfun::graph::invert_binary_tree;

    using forfun::graph::binary_tree_node;

    binary_tree_node h_r_r_l_l{12};
    binary_tree_node h_r_l_l{8};
    binary_tree_node h_r_l_r{9};
    binary_tree_node h_r_r_l{10, &h_r_r_l_l, nullptr};
    binary_tree_node h_r_r_r{11};
    binary_tree_node h_l_l{4};
    binary_tree_node h_l_r{5};
    binary_tree_node h_r_l{6, &h_r_l_l, &h_r_l_r};
    binary_tree_node h_r_r{7, &h_r_r_l, &h_r_r_r};
    binary_tree_node h_l{2, &h_l_l, &h_l_r};
    binary_tree_node h_r{3, &h_r_l, &h_r_r};
    binary_tree_node root{1, &h_l, &h_r};

    ankerl::nanobench::Bench()

        .title("Invert binary tree")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::invert_binary_tree).c_str(),
            [&root] -> void { iterative::invert_binary_tree(root); }
        )

        .run(
            NAMEOF_RAW(recursive::invert_binary_tree).c_str(),
            [&root] noexcept -> void { recursive::invert_binary_tree(root); }
        )

        ;
}
