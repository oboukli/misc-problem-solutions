// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/binary_tree_node.hpp"
#include "forfun/graph/invert_binary_tree.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Invert binary tree",
    "[invert_binary_tree]",
    (auto invert_binary_tree, invert_binary_tree),
    forfun::graph::invert_binary_tree::iterative::invert_binary_tree,
    forfun::graph::invert_binary_tree::recursive::invert_binary_tree
)
{
    using forfun::graph::binary_tree_node;

    SECTION("One node graph")
    {
        binary_tree_node root{11};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == nullptr);
        REQUIRE(root.right_node_ == nullptr);
        REQUIRE(root.value_ == 11);
    }

    SECTION("Two node graph (case 1)")
    {
        binary_tree_node h_l{13};
        binary_tree_node root{11, &h_l, nullptr};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == nullptr);
        REQUIRE(root.right_node_ == &h_l);
        REQUIRE(root.value_ == 11);

        REQUIRE(root.right_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_ == nullptr);
        REQUIRE(root.right_node_->value_ == 13);
    }

    SECTION("Two node graph (case 2)")
    {
        binary_tree_node h_r{17};
        binary_tree_node root{11, nullptr, &h_r};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == &h_r);
        REQUIRE(root.right_node_ == nullptr);
        REQUIRE(root.value_ == 11);

        REQUIRE(root.left_node_->left_node_ == nullptr);
        REQUIRE(root.left_node_->right_node_ == nullptr);
        REQUIRE(root.left_node_->value_ == 17);
    }

    SECTION("Three-node balanced tree")
    {
        binary_tree_node h_l{13};
        binary_tree_node h_r{17};
        binary_tree_node root{11, &h_l, &h_r};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == &h_r);
        REQUIRE(root.right_node_ == &h_l);
        REQUIRE(root.value_ == 11);

        REQUIRE(root.left_node_->left_node_ == nullptr);
        REQUIRE(root.left_node_->right_node_ == nullptr);
        REQUIRE(root.left_node_->value_ == 17);

        REQUIRE(root.right_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_ == nullptr);
        REQUIRE(root.right_node_->value_ == 13);
    }

    SECTION("Three-node unbalanced tree (case 1)")
    {
        binary_tree_node h_l_l{17};
        binary_tree_node h_l{13, &h_l_l, nullptr};
        binary_tree_node root{11, &h_l, nullptr};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == nullptr);
        REQUIRE(root.right_node_ == &h_l);
        REQUIRE(root.value_ == 11);

        REQUIRE(root.right_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_ == &h_l_l);
        REQUIRE(root.right_node_->value_ == 13);

        REQUIRE(root.right_node_->right_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_->right_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_->value_ == 17);
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
        binary_tree_node root{1, &h_l, &h_r};

        invert_binary_tree(root);

        REQUIRE(root.left_node_ == &h_r);
        REQUIRE(root.right_node_ == &h_l);
        REQUIRE(root.value_ == 1);

        REQUIRE(root.left_node_->left_node_ == &h_r_r);
        REQUIRE(root.left_node_->right_node_ == &h_r_l);
        REQUIRE(root.left_node_->value_ == 3);
        REQUIRE(root.right_node_->left_node_ == &h_l_r);
        REQUIRE(root.right_node_->right_node_ == &h_l_l);
        REQUIRE(root.right_node_->value_ == 2);

        REQUIRE(root.left_node_->left_node_->left_node_ == &h_r_r_r);
        REQUIRE(root.left_node_->left_node_->right_node_ == &h_r_r_l);
        REQUIRE(root.left_node_->left_node_->value_ == 7);
        REQUIRE(root.left_node_->right_node_->left_node_ == &h_r_l_r);
        REQUIRE(root.left_node_->right_node_->right_node_ == &h_r_l_l);
        REQUIRE(root.left_node_->right_node_->value_ == 6);
        REQUIRE(root.right_node_->left_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->left_node_->right_node_ == nullptr);
        REQUIRE(root.right_node_->left_node_->value_ == 5);
        REQUIRE(root.right_node_->right_node_->left_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_->right_node_ == nullptr);
        REQUIRE(root.right_node_->right_node_->value_ == 4);

        REQUIRE(root.left_node_->left_node_->left_node_->left_node_ == nullptr);
        REQUIRE(
            root.left_node_->left_node_->left_node_->right_node_ == nullptr
        );
        REQUIRE(root.left_node_->left_node_->left_node_->value_ == 11);
        REQUIRE(
            root.left_node_->left_node_->right_node_->left_node_ == nullptr
        );
        REQUIRE(
            root.left_node_->left_node_->right_node_->right_node_ == &h_r_r_l_l
        );
        REQUIRE(root.left_node_->left_node_->right_node_->value_ == 10);
        REQUIRE(
            root.left_node_->right_node_->left_node_->left_node_ == nullptr
        );
        REQUIRE(
            root.left_node_->right_node_->left_node_->right_node_ == nullptr
        );
        REQUIRE(root.left_node_->right_node_->left_node_->value_ == 9);
        REQUIRE(
            root.left_node_->right_node_->right_node_->left_node_ == nullptr
        );
        REQUIRE(
            root.left_node_->right_node_->right_node_->right_node_ == nullptr
        );
        REQUIRE(root.left_node_->right_node_->right_node_->value_ == 8);
    }
}
