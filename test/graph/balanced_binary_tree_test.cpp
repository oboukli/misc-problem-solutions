// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/balanced_binary_tree.hpp"
#include "forfun/graph/binary_tree_node.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Balanced binary tree",
    "[balanced_binary_tree]",
    (auto is_balanced, is_balanced),
    forfun::graph::balanced_binary_tree::complicated::is_balanced,
    forfun::graph::balanced_binary_tree::hacky::is_balanced
)
{
    using forfun::graph::balanced_binary_tree::binary_tree_node;

    SECTION("Empty graph")
    {
        REQUIRE(is_balanced(nullptr));
    }

    SECTION("One node graph")
    {
        binary_tree_node const root{11};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Two node graph (case 1)")
    {
        binary_tree_node h_l{13};
        binary_tree_node const root{11, &h_l, nullptr};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Two node graph (case 2)")
    {
        binary_tree_node h_r{17};
        binary_tree_node const root{11, nullptr, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Three-node balanced tree")
    {
        binary_tree_node h_l{13};
        binary_tree_node h_r{17};
        binary_tree_node const root{11, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Three-node unbalanced tree (case 1)")
    {
        binary_tree_node h_l_l{17};
        binary_tree_node h_l{13, &h_l_l, nullptr};
        binary_tree_node const root{11, &h_l, nullptr};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Three-node unbalanced tree (case 2)")
    {
        binary_tree_node h_l_r{17};
        binary_tree_node h_l{13, nullptr, &h_l_r};
        binary_tree_node const root{11, &h_l, nullptr};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Three-node unbalanced tree (case 3)")
    {
        binary_tree_node h_r_l{17};
        binary_tree_node h_r{13, &h_r_l, nullptr};
        binary_tree_node const root{11, nullptr, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Three-node unbalanced tree (case 4)")
    {
        binary_tree_node h_r_r{17};
        binary_tree_node h_r{13, nullptr, &h_r_r};
        binary_tree_node const root{11, nullptr, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Four-node balanced tree")
    {
        binary_tree_node h_l_l{19};
        binary_tree_node h_l{13, &h_l_l, nullptr};
        binary_tree_node h_r{17};
        binary_tree_node const root{11, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Four-node unbalanced tree (case 1)")
    {
        binary_tree_node h_r_l_r{19};
        binary_tree_node h_r_l{17, nullptr, &h_r_l_r};
        binary_tree_node h_r{13, &h_r_l, nullptr};
        binary_tree_node const root{11, nullptr, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Four-node unbalanced tree (case 2)")
    {
        binary_tree_node h_r_l{17};
        binary_tree_node h_r_r{19};
        binary_tree_node h_l{13, &h_r_l, &h_r_r};
        binary_tree_node const root{11, &h_l, nullptr};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Twelve-node balanced tree")
    {
        // As seen in graph 3 in graph docs.
        binary_tree_node h_r_l_l{8};
        binary_tree_node h_r_l_r{9};
        binary_tree_node h_r_r_l{10};
        binary_tree_node h_r_r_r{11};
        binary_tree_node h_l_l{4};
        binary_tree_node h_l_r{5};
        binary_tree_node h_r_l{6, &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{7, &h_r_r_l, &h_r_r_r};
        binary_tree_node h_l{2, &h_l_l, &h_l_r};
        binary_tree_node h_r{3, &h_r_l, &h_r_r};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("Twelve-node unbalanced tree (benchmark case)")
    {
        // As seen in graph 4 in graph docs.
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
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("Twelve-node unbalanced tree (unbalanced on the left side)")
    {
        binary_tree_node h_l_l_l_l{13};
        binary_tree_node h_l_l_l{8, &h_l_l_l_l, nullptr};
        binary_tree_node h_r_l_l{9};
        binary_tree_node h_r_l_r{10};
        binary_tree_node h_r_r_l{11};
        binary_tree_node h_r_r_r{12};
        binary_tree_node h_l_l{4, &h_l_l_l, nullptr};
        binary_tree_node h_l_r{5};
        binary_tree_node h_r_l{6, &h_r_l_l, &h_r_l_r};
        binary_tree_node h_r_r{7, &h_r_r_l, &h_r_r_r};
        binary_tree_node h_l{2, &h_l_l, &h_l_r};
        binary_tree_node h_r{3, &h_r_l, &h_r_r};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("LeetCode (case 1)")
    {
        binary_tree_node h_r_l{15};
        binary_tree_node h_r_r{7};
        binary_tree_node h_l{9};
        binary_tree_node h_r{20, &h_r_l, &h_r_r};
        binary_tree_node const root{3, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("LeetCode (case 2)")
    {
        binary_tree_node h_l_l_l{4};
        binary_tree_node h_l_l_r{4};
        binary_tree_node h_l_l{3, &h_l_l_l, &h_l_l_r};
        binary_tree_node h_l_r{3};
        binary_tree_node h_l{2, &h_l_l, &h_l_r};
        binary_tree_node h_r{2};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("NeetCode (case 1)")
    {
        binary_tree_node h_r_l{4};
        binary_tree_node h_l{2};
        binary_tree_node h_r{3, &h_r_l, nullptr};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("NeetCode (case 2)")
    {
        binary_tree_node h_r_l_l{5};
        binary_tree_node h_r_l{4, &h_r_l_l, nullptr};
        binary_tree_node h_l{2};
        binary_tree_node h_r{3, &h_r_l, nullptr};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("GeeksforGeeks (case 1)")
    {
        binary_tree_node h_l_l_l{8};
        binary_tree_node h_l_r{5};
        binary_tree_node h_l_l{4, &h_l_l_l, nullptr};
        binary_tree_node h_l{2, &h_l_l, &h_l_r};
        binary_tree_node h_r{3};
        binary_tree_node const root{1, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("GeeksforGeeks (case 2)")
    {
        binary_tree_node h_r_l{15};
        binary_tree_node h_r_r{20};
        binary_tree_node h_l{5};
        binary_tree_node h_r{30, &h_r_l, &h_r_r};
        binary_tree_node const root{10, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }

    SECTION("GeeksforGeeks (case 3)")
    {
        binary_tree_node h_l_l_l{5};
        binary_tree_node h_l_l{3, &h_l_l_l, nullptr};
        binary_tree_node h_l_r{4};
        binary_tree_node h_l{1, &h_l_l, &h_l_r};
        binary_tree_node h_r{2};
        binary_tree_node const root{0, &h_l, &h_r};

        REQUIRE_FALSE(is_balanced(&root));
    }

    SECTION("GeeksforGeeks (case 4)")
    {
        binary_tree_node h_l_l{3};
        binary_tree_node h_l_r{4};
        binary_tree_node h_l{1, &h_l_l, &h_l_r};
        binary_tree_node h_r{2};
        binary_tree_node const root{0, &h_l, &h_r};

        REQUIRE(is_balanced(&root));
    }
}

// Web references:
// https://leetcode.com/problems/balanced-binary-tree/
// https://neetcode.io/problems/balanced-binary-tree
// https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
// https://www.geeksforgeeks.org/balanced-binary-tree/
