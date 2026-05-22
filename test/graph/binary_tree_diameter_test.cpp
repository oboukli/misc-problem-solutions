// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/binary_tree_diameter.hpp"
#include "forfun/graph/binary_tree_node.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Diameter of binary tree",
    "[binary_tree_diameter]",
    (auto measure_diameter, measure_diameter),
    forfun::graph::binary_tree_diameter::iterative::measure_diameter,
    forfun::graph::binary_tree_diameter::recursive::measure_diameter,
    forfun::graph::binary_tree_diameter::recursive_lambda::measure_diameter
)
{
    using forfun::graph::binary_tree_node;

    SECTION("One node graph")
    {
        binary_tree_node const root{'a'};

        REQUIRE(measure_diameter(root) == 0UZ);
    }

    SECTION("Two node graph (case 1)")
    {
        binary_tree_node h_l{'b'};
        binary_tree_node const root{'a', &h_l, nullptr};

        REQUIRE(measure_diameter(root) == 1UZ);
    }

    SECTION("Two node graph (case 2)")
    {
        binary_tree_node h_r{'b'};
        binary_tree_node const root{'a', nullptr, &h_r};

        REQUIRE(measure_diameter(root) == 1UZ);
    }

    SECTION("Three-node balanced tree")
    {
        binary_tree_node h_l{'b'};
        binary_tree_node h_r{'c'};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Three-node unbalanced tree (case 1)")
    {
        binary_tree_node h_l_l{'c'};
        binary_tree_node h_l{'b', &h_l_l, nullptr};
        binary_tree_node const root{'a', &h_l, nullptr};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Three-node unbalanced tree (case 2)")
    {
        binary_tree_node h_l_r{'c'};
        binary_tree_node h_l{'b', nullptr, &h_l_r};
        binary_tree_node const root{'a', &h_l, nullptr};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Three-node unbalanced tree (case 3)")
    {
        binary_tree_node h_r_l{'c'};
        binary_tree_node h_r{'b', &h_r_l, nullptr};
        binary_tree_node const root{'a', nullptr, &h_r};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Three-node unbalanced tree (case 4)")
    {
        binary_tree_node h_r_r{'c'};
        binary_tree_node h_r{'b', nullptr, &h_r_r};
        binary_tree_node const root{'a', nullptr, &h_r};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Four-node balanced tree")
    {
        binary_tree_node h_l_l{'d'};
        binary_tree_node h_l{'b', &h_l_l, nullptr};
        binary_tree_node h_r{'c'};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 3UZ);
    }

    SECTION("Four-node unbalanced tree (case 1)")
    {
        binary_tree_node h_r_l_r{'d'};
        binary_tree_node h_r_l{'c', nullptr, &h_r_l_r};
        binary_tree_node h_r{'b', &h_r_l, nullptr};
        binary_tree_node const root{'a', nullptr, &h_r};

        REQUIRE(measure_diameter(root) == 3UZ);
    }

    SECTION("Four-node unbalanced tree (case 2)")
    {
        binary_tree_node h_r_l{'c'};
        binary_tree_node h_r_r{'d'};
        binary_tree_node h_l{'b', &h_r_l, &h_r_r};
        binary_tree_node const root{'a', &h_l, nullptr};

        REQUIRE(measure_diameter(root) == 2UZ);
    }

    SECTION("Twelve-node balanced tree")
    {
        // As seen in graph 3 in graph docs.
        binary_tree_node h_r_l_l{'h'};
        binary_tree_node h_r_l_r{'i'};
        binary_tree_node h_r_r_l{'j'};
        binary_tree_node h_r_r_r{'k'};
        binary_tree_node h_l_l{'d'};
        binary_tree_node h_l_r{'e'};
        binary_tree_node h_r_l{'f', &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{'g', &h_r_r_l, &h_r_r_r};
        binary_tree_node h_l{'b', &h_l_l, &h_l_r};
        binary_tree_node h_r{'c', &h_r_l, &h_r_r};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 5UZ);
    }

    SECTION("Twelve-node unbalanced tree (benchmark case)")
    {
        // As seen in graph 4 in graph docs.
        binary_tree_node h_r_r_l_l{'l'};
        binary_tree_node h_r_l_l{'h'};
        binary_tree_node h_r_l_r{'i'};
        binary_tree_node h_r_r_l{'j', &h_r_r_l_l, nullptr};
        binary_tree_node h_r_r_r{'k'};
        binary_tree_node h_l_l{'d'};
        binary_tree_node h_l_r{'e'};
        binary_tree_node h_r_l{'f', &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{'g', &h_r_r_l, &h_r_r_r};
        binary_tree_node h_l{'b', &h_l_l, &h_l_r};
        binary_tree_node h_r{'c', &h_r_l, &h_r_r};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 6UZ);
    }

    SECTION("Twelve-node unbalanced tree (unbalanced on the left side)")
    {
        // As seen in graph 5 in graph docs.
        binary_tree_node h_l_l_l_l{'m'};
        binary_tree_node h_l_l_l{'h', &h_l_l_l_l, nullptr};
        binary_tree_node h_r_l_l{'i'};
        binary_tree_node h_r_l_r{'j'};
        binary_tree_node h_r_r_l{'k'};
        binary_tree_node h_r_r_r{'l'};
        binary_tree_node h_l_l{'d', &h_l_l_l, nullptr};
        binary_tree_node h_l_r{'e'};
        binary_tree_node h_r_l{'f', &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{'g', &h_r_r_l, &h_r_r_r};
        binary_tree_node h_l{'b', &h_l_l, &h_l_r};
        binary_tree_node h_r{'c', &h_r_l, &h_r_r};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 7UZ);
    }

    SECTION("LeetCode case")
    {
        binary_tree_node h_l_l{'d'};
        binary_tree_node h_l_r{'e'};
        binary_tree_node h_l{'b', &h_l_l, &h_l_r};
        binary_tree_node h_r{'c'};
        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 3UZ);
    }

    SECTION("NeetCode case")
    {
        binary_tree_node h_r_l_l{'f'};
        binary_tree_node h_r_l{'c', &h_r_l_l, nullptr};
        binary_tree_node h_r_r{'d'};
        binary_tree_node h_r{'b', &h_r_l, &h_r_r};
        binary_tree_node const root{'a', nullptr, &h_r};

        REQUIRE(measure_diameter(root) == 3UZ);
    }

    SECTION("Nineteen-node unbalanced binary tree (benchmark case)")
    {
        // As seen in graph 6 in graph docs.
        binary_tree_node h_l_l_l_l_l_l{'r'};
        binary_tree_node h_l_r_l_l_l_l{'s'};

        binary_tree_node h_l_l_l_l_l{'p', &h_l_l_l_l_l_l, nullptr};
        binary_tree_node h_l_r_l_l_l{'q', &h_l_r_l_l_l_l, nullptr};

        binary_tree_node h_l_l_l_l{'n', &h_l_l_l_l_l, nullptr};
        binary_tree_node h_l_r_l_l{'o', &h_l_r_l_l_l, nullptr};

        binary_tree_node h_l_l_l{'h', &h_l_l_l_l, nullptr};
        binary_tree_node h_l_r_l{'i', &h_l_r_l_l, nullptr};
        binary_tree_node h_r_r_l{'j'};
        binary_tree_node h_r_r_r{'k'};
        binary_tree_node h_r_l_l{'l'};
        binary_tree_node h_r_l_r{'m'};

        binary_tree_node h_l_l{'d', &h_l_l_l, nullptr};
        binary_tree_node h_l_r{'e', &h_l_r_l, nullptr};
        binary_tree_node h_r_l{'f', &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{'g', &h_r_r_l, &h_r_r_r};

        binary_tree_node h_l{'b', &h_l_l, &h_l_r};
        binary_tree_node h_r{'c', &h_r_l, &h_r_r};

        binary_tree_node const root{'a', &h_l, &h_r};

        REQUIRE(measure_diameter(root) == 10UZ);
    }
}

// References:
// https://leetcode.com/problems/diameter-of-binary-tree/
// https://neetcode.io/problems/binary-tree-diameter
