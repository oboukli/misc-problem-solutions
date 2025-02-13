// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/binary_tree_node.hpp"

TEST_CASE("Binary tree node", "[binary_tree_node_static]")
{
    SECTION("Constructor 1")
    {
        constexpr forfun::graph::binary_tree_node const node{};

        STATIC_REQUIRE(node.left_node_ == nullptr);
        STATIC_REQUIRE(node.right_node_ == nullptr);
        STATIC_REQUIRE(node.value_ == decltype(node)::value_type{0});
    }

    SECTION("Constructor 2")
    {
        constexpr forfun::graph::binary_tree_node const node{136279841};

        STATIC_REQUIRE(node.left_node_ == nullptr);
        STATIC_REQUIRE(node.right_node_ == nullptr);
        STATIC_REQUIRE(node.value_ == decltype(node)::value_type{136279841});
    }
}
