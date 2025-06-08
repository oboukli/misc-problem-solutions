// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/graph/invert_binary_tree.hpp"

#include <deque>
#include <utility>

#include "forfun/graph/binary_tree_node.hpp"

namespace forfun::graph::invert_binary_tree {

auto invert_binary_tree(binary_tree_node& root) -> void
{
    std::deque<binary_tree_node*> tracker{};

    tracker.push_back(&root);

    while (not tracker.empty())
    {
        binary_tree_node* node{tracker.front()};
        tracker.pop_front();

        std::swap(node->left_node_, node->right_node_);

        if (node->left_node_ != nullptr)
        {
            tracker.push_back(node->left_node_);
        }

        if (node->right_node_ != nullptr)
        {
            tracker.push_back(node->right_node_);
        }
    }
}

} // namespace forfun::graph::invert_binary_tree
