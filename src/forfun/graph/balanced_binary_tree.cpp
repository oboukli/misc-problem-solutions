// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/graph/balanced_binary_tree.hpp"

#include <algorithm>
#include <cstddef>

namespace forfun::graph::balanced_binary_tree {

namespace simple {

namespace {

auto measure_depth_internal(binary_tree_node const* const head) noexcept
    -> std::size_t
{
    if (head == nullptr)
    {
        return std::size_t{0U};
    }

    // clang-format off
    return std::size_t{1U} + std::max(
        measure_depth_internal(head->left_node_),
        measure_depth_internal(head->right_node_)
    );
    // clang-format on
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const head) noexcept
    -> bool
{
    if (head == nullptr)
    {
        return true;
    }

    auto depth_lhs{measure_depth_internal(head->left_node_)};
    auto depth_rhs{measure_depth_internal(head->right_node_)};

    auto diff{
        depth_lhs > depth_rhs ? depth_lhs - depth_rhs : depth_rhs - depth_lhs
    };

    return diff <= std::size_t{1U};
}

} // namespace simple

} // namespace forfun::graph::balanced_binary_tree
