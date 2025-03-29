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
    if (head == nullptr) [[unlikely]]
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
        return {diff, true};
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

namespace hacky {

namespace {

auto measure_depth_internal(binary_tree_node const* const head) noexcept -> int
{
    if (head == nullptr) [[unlikely]]
    {
        return 0;
    }

    auto const left{measure_depth_internal(head->left_node_)};
    if (left == -1)
    {
        return -1;
    }

    auto const right{measure_depth_internal(head->right_node_)};
    if (right == -1)
    {
        return -1;
    }

    auto diff{left > right ? left - right : right - left};

    if (diff > 1)
    {
        return -1;
    }

    return 1 + std::max(left, right);
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const head) noexcept
    -> bool
{
    return measure_depth_internal(head) != -1;
}

} // namespace hacky

} // namespace forfun::graph::balanced_binary_tree
