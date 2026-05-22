// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/diameter-of-binary-tree/

#ifndef FORFUN_GRAPH_BINARY_TREE_DIAMETER_HPP_
#define FORFUN_GRAPH_BINARY_TREE_DIAMETER_HPP_

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <utility>

#include "forfun/graph/binary_tree_node.hpp"

namespace forfun::graph::binary_tree_diameter {

namespace iterative {

[[nodiscard]] auto measure_diameter(binary_tree_node const& root)
    -> std::size_t;

} // namespace iterative

namespace recursive {

namespace detail {

[[nodiscard]] constexpr auto measure_depth(
    binary_tree_node const* const node, std::size_t& max_diameter
) noexcept -> std::size_t
{
    if (node == nullptr)
    {
        return 0UZ;
    }

    auto const left{measure_depth(node->left_node_, max_diameter)};
    auto const right{measure_depth(node->right_node_, max_diameter)};

    max_diameter = std::max(max_diameter, left + right);

    return std::max(left, right) + 1UZ;
}

} // namespace detail

[[nodiscard]] constexpr auto
measure_diameter(binary_tree_node const& root) noexcept -> std::size_t
{
    std::size_t max_diameter{0};

    std::ignore = detail::measure_depth(&root, max_diameter);

    return max_diameter;
}

} // namespace recursive

namespace recursive_lambda {

[[nodiscard]] constexpr auto
measure_diameter(binary_tree_node const& root) noexcept -> std::size_t
{
    std::size_t max_diameter{0};

    auto const measure_depth{
        [&max_diameter] [[nodiscard]] (
            this auto const& self, binary_tree_node const* const node
        ) noexcept -> std::size_t {
            if (node == nullptr)
            {
                return 0UZ;
            }

            auto const left{self(node->left_node_)};
            auto const right{self(node->right_node_)};

            max_diameter = std::max(max_diameter, left + right);

            return std::max(left, right) + 1UZ;
        }
    };

    std::ignore = measure_depth(&root);

    return max_diameter;
}

} // namespace recursive_lambda

} // namespace forfun::graph::binary_tree_diameter

#endif // FORFUN_GRAPH_BINARY_TREE_DIAMETER_HPP_
