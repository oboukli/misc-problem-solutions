// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_VERTEX_HPP_
#define FORFUN_GRAPH_VERTEX_HPP_

#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace forfun::graph {

template <typename Vertex>
    requires std::is_trivially_copyable_v<Vertex>
using vertex_adjacency_list = std::unordered_map<Vertex, std::vector<Vertex>>;

template <typename Vertex>
    requires std::is_trivially_copyable_v<Vertex>
using vertex_state_list = std::unordered_set<Vertex>;

} // namespace forfun::graph

#endif // FORFUN_GRAPH_VERTEX_HPP_
