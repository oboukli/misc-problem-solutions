// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/binary_tree_node.hpp"

TEST_CASE("Binary tree node", "[binary_tree_node]")
{
    SECTION("Constructor 1")
    {
        forfun::graph::binary_tree_node const node{};

        REQUIRE(node.left_node_ == nullptr);
        REQUIRE(node.right_node_ == nullptr);
        REQUIRE(node.value_ == decltype(node)::value_type{0});
    }

    SECTION("Constructor 2")
    {
        forfun::graph::binary_tree_node const node{77232917};

        REQUIRE(node.left_node_ == nullptr);
        REQUIRE(node.right_node_ == nullptr);
        REQUIRE(node.value_ == decltype(node)::value_type{77232917});
    }

    SECTION("Constructor 3")
    {
        forfun::graph::binary_tree_node left{};
        forfun::graph::binary_tree_node right{};
        forfun::graph::binary_tree_node const node{74207281, &left, &right};

        REQUIRE(node.left_node_ == &left);
        REQUIRE(node.right_node_ == &right);
        REQUIRE(node.value_ == decltype(node)::value_type{74207281});
    }
}
