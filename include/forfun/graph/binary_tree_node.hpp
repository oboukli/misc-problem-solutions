// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_BINARY_TREE_NODE_HPP_
#define FORFUN_GRAPH_BINARY_TREE_NODE_HPP_

namespace forfun::graph {

class [[nodiscard]] binary_tree_node final {
public:
    using value_type = int;

    explicit constexpr binary_tree_node() noexcept :
        value_{}, left_node_{nullptr}, right_node_{nullptr}
    {
    }

    explicit constexpr binary_tree_node(value_type value) noexcept :
        value_{value}, left_node_{nullptr}, right_node_{nullptr}
    {
    }

    explicit binary_tree_node(
        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        value_type value,
        binary_tree_node* left,
        binary_tree_node* right
        // NOLINTEND(bugprone-easily-swappable-parameters)
    ) noexcept :
        value_{value}, left_node_{left}, right_node_{right}
    {
    }

    value_type value_;

    binary_tree_node* left_node_;

    binary_tree_node* right_node_;
};

} // namespace forfun::graph

#endif // FORFUN_GRAPH_BINARY_TREE_NODE_HPP_
