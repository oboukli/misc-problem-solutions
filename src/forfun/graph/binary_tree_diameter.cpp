// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/graph/binary_tree_diameter.hpp"

#include <algorithm>
#include <cstddef>
#include <stack>
#include <unordered_map>

#include "forfun/graph/binary_tree_node.hpp"

namespace forfun::graph::binary_tree_diameter::iterative {

namespace {

using Pointer = binary_tree_node const*;

[[nodiscard]] inline auto is_visited(
    std::unordered_map<Pointer, std::size_t> const& tracker, Pointer const node
) noexcept -> bool
{
    return tracker.contains(node);
}

[[nodiscard]] inline auto get_height(
    std::unordered_map<Pointer, std::size_t> const& tracker, Pointer const node
) noexcept -> std::size_t
{
    if (node == nullptr) [[unlikely]]
    {
        return 0UZ;
    }

    return tracker.find(node)->second;
}

} // namespace

[[nodiscard]] auto measure_diameter(binary_tree_node const& root) -> std::size_t
{
    std::size_t max_diameter{0};

    std::unordered_map<Pointer, std::size_t> heights{};

    std::stack<Pointer> node_stack{};
    node_stack.push(&root);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        Pointer const node{node_stack.top()};

        if ((node->left_node_ != nullptr)
            && not is_visited(heights, node->left_node_))
        {
            node_stack.push(node->left_node_);

            continue;
        }

        if (node->right_node_ != nullptr
            && not is_visited(heights, node->right_node_))
        {
            node_stack.push(node->right_node_);

            continue;
        }

        node_stack.pop();

        auto const left{get_height(heights, node->left_node_)};
        auto const right{get_height(heights, node->right_node_)};

        max_diameter = std::max(max_diameter, left + right);

        heights.insert({node, std::max(left, right) + 1UZ});
    } while (not std::empty(node_stack));

    return max_diameter;
}

} // namespace forfun::graph::binary_tree_diameter::iterative
