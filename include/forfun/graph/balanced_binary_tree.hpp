// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_BALANCED_BINARY_TREE_HPP_
#define FORFUN_GRAPH_BALANCED_BINARY_TREE_HPP_

#include "forfun/graph/binary_tree_node.hpp"

namespace forfun::graph::balanced_binary_tree {

using forfun::graph::binary_tree_node;

namespace complicated {

[[nodiscard]] auto is_balanced(binary_tree_node const* head) noexcept -> bool;

} // namespace complicated

namespace simple {

[[nodiscard]] auto is_balanced(binary_tree_node const* head) noexcept -> bool;

} // namespace simple

} // namespace forfun::graph::balanced_binary_tree

#endif // FORFUN_GRAPH_BALANCED_BINARY_TREE_HPP_
