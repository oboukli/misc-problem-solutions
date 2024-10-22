// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/graph/balanced_binary_tree.hpp"

#include <algorithm>
#include <cstddef>
#include <utility>

namespace forfun::graph::balanced_binary_tree {

namespace complicated {

namespace {

auto is_unbalanced_internal(binary_tree_node const* const head) noexcept
    -> std::pair<std::size_t, bool>
{
    if (head == nullptr)
    {
        return {std::size_t{0U}, false};
    }

    auto const left{is_unbalanced_internal(head->left_node_)};
    if (left.second)
    {
        return left;
    }

    auto const right{is_unbalanced_internal(head->right_node_)};
    if (right.second)
    {
        return right;
    }

    // clang-format off
    auto diff{
        left.first > right.first
        ? left.first - right.first
        : right.first - left.first
    };
    // clang-format on

    if (diff > std::size_t{1U})
    {
        return {diff, true}; // Or {0, true}
    }

    return {std::size_t{1} + std::max(left.first, right.first), false};
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const head) noexcept
    -> bool
{
    return not is_unbalanced_internal(head).second;
}

} // namespace complicated

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
