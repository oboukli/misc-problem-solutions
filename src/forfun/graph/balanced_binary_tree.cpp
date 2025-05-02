// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/graph/balanced_binary_tree.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <utility>

namespace forfun::graph::balanced_binary_tree {

namespace raw {

namespace {

auto measure_depth_internal(binary_tree_node const* const root) noexcept
    -> std::ptrdiff_t
{
    if (root == nullptr)
    {
        return 0;
    }

    auto const left{measure_depth_internal(root->left_node_)};

    if (left == std::ptrdiff_t{-1})
    {
        return -1;
    }

    auto const right{measure_depth_internal(root->right_node_)};

    if (right == std::ptrdiff_t{-1})
    {
        return -1;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    std::ptrdiff_t min /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    std::ptrdiff_t max /*[[indeterminate]]*/;

    if (left < right)
    {
        min = left;
        max = right;
    }
    else
    {
        min = right;
        max = left;
    }

    if ((max - min) > std::ptrdiff_t{1})
    {
        return -1;
    }

    return ++max;
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const root) noexcept
    -> bool
{
    return measure_depth_internal(root) != std::ptrdiff_t{-1};
}

} // namespace raw

namespace stl_abs {

namespace {

auto is_unbalanced_internal(binary_tree_node const* const root) noexcept
    -> std::pair<std::size_t, bool>
{
    if (root == nullptr)
    {
        return {0UZ, false};
    }

    auto const left{is_unbalanced_internal(root->left_node_)};

    if (left.second)
    {
        return left;
    }

    auto const right{is_unbalanced_internal(root->right_node_)};

    if (right.second)
    {
        return right;
    }

    auto const diff{std::abs(
        static_cast<std::ptrdiff_t>(left.first)
        - static_cast<std::ptrdiff_t>(right.first)
    )};
    if (diff > decltype(diff){1})
    {
        return {diff, true};
    }

    return {std::max(left.first, right.first) + 1UZ, false};
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const root) noexcept
    -> bool
{
    return not is_unbalanced_internal(root).second;
}

} // namespace stl_abs

namespace stl_minmax {

namespace {

auto is_unbalanced_internal(binary_tree_node const* const root) noexcept
    -> std::pair<std::size_t, bool>
{
    if (root == nullptr)
    {
        return {0UZ, false};
    }

    auto const left{is_unbalanced_internal(root->left_node_)};

    if (left.second)
    {
        return left;
    }

    auto const right{is_unbalanced_internal(root->right_node_)};

    if (right.second)
    {
        return right;
    }

    auto const [min, max]{std::minmax(left.first, right.first)};

    std::size_t const diff{max - min};
    if (diff > 1UZ)
    {
        return {diff, true};
    }

    return {max + 1UZ, false};
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const root) noexcept
    -> bool
{
    return not is_unbalanced_internal(root).second;
}

} // namespace stl_minmax

namespace stl_pair {

namespace {

auto is_unbalanced_internal(binary_tree_node const* const root) noexcept
    -> std::pair<std::size_t, bool>
{
    if (root == nullptr)
    {
        return {0UZ, false};
    }

    auto const left{is_unbalanced_internal(root->left_node_)};

    if (left.second)
    {
        return left;
    }

    auto const right{is_unbalanced_internal(root->right_node_)};
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

    if (diff > 1UZ)
    {
        return {diff, true};
    }

    return {std::max(left.first, right.first) + 1UZ, false};
}

} // namespace

[[nodiscard]] auto is_balanced(binary_tree_node const* const root) noexcept
    -> bool
{
    return not is_unbalanced_internal(root).second;
}

} // namespace stl_pair

} // namespace forfun::graph::balanced_binary_tree
