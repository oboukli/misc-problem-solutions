// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/graph/binary_tree_diameter.hpp"
#include "forfun/graph/binary_tree_node.hpp"

TEST_CASE(
    "Diameter of binary tree benchmarking", "[benchmark][binary_tree_diameter]"
)
{
    using namespace forfun::graph::binary_tree_diameter;

    using forfun::graph::binary_tree_node;

    // As seen in graph 6 in graph docs.
    binary_tree_node h_l_l_l_l_l_l{18};
    binary_tree_node h_l_r_l_l_l_l{19};

    binary_tree_node h_l_l_l_l_l{16, &h_l_l_l_l_l_l, nullptr};
    binary_tree_node h_l_r_l_l_l{17, &h_l_r_l_l_l_l, nullptr};

    binary_tree_node h_l_l_l_l{14, &h_l_l_l_l_l, nullptr};
    binary_tree_node h_l_r_l_l{15, &h_l_r_l_l_l, nullptr};

    binary_tree_node h_l_l_l{8, &h_l_l_l_l, nullptr};
    binary_tree_node h_l_r_l{9, &h_l_r_l_l, nullptr};
    binary_tree_node h_r_r_l{10};
    binary_tree_node h_r_r_r{11};
    binary_tree_node h_r_l_l{12};
    binary_tree_node h_r_l_r{13};

    binary_tree_node h_l_l{4, &h_l_l_l, nullptr};
    binary_tree_node h_l_r{5, &h_l_r_l, nullptr};
    binary_tree_node h_r_l{6, &h_r_l_l, &h_r_l_r};
    binary_tree_node h_r_r{7, &h_r_r_l, &h_r_r_r};

    binary_tree_node h_l{2, &h_l_l, &h_l_r};
    binary_tree_node h_r{3, &h_r_l, &h_r_r};

    binary_tree_node const root{1, &h_l, &h_r};

    ankerl::nanobench::Bench()

        .title("Diameter of binary tree")
        .relative(true)

        .run(
            NAMEOF_RAW(iterative::measure_diameter).c_str(),
            [&root] noexcept -> void {
                auto const volatile r{iterative::measure_diameter(root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::measure_diameter).c_str(),
            [&root] noexcept -> void {
                auto const volatile r{recursive::measure_diameter(root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(recursive_lambda::measure_diameter).c_str(),
            [&root] noexcept -> void {
                auto const volatile r{recursive_lambda::measure_diameter(root)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
