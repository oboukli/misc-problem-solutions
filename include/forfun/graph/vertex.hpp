// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_VERTEX_HPP_
#define FORFUN_GRAPH_VERTEX_HPP_

#ifndef __cpp_lib_containers_ranges
#include <algorithm>
#include <iterator>
#endif // __cpp_lib_containers_ranges

#include <concepts>
#include <ranges>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace forfun::graph {

enum struct vertex_visit_state : bool {
    unvisited = false,
    visited = true,
};

template <typename Vertex>
    requires std::is_trivially_copyable_v<Vertex>
using vertex_adjacency_list = std::unordered_map<Vertex, std::vector<Vertex>>;

template <typename Vertex>
    requires std::is_trivially_copyable_v<Vertex>
using vertex_state_list = std::unordered_map<Vertex, vertex_visit_state>;

template <typename Vertex>
auto init_state_list(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_state_list<Vertex>& state_list
) -> void
{
    auto const transformer{
        [](auto const& p) noexcept -> std::pair<Vertex, vertex_visit_state> {
            return std::make_pair(p.first, vertex_visit_state::unvisited);
        }
    };

#ifdef __cpp_lib_containers_ranges
    state_list.insert_range(
        adjacency_list
#ifdef __cpp_lib_ranges_as_const
        | std::views::as_const
#endif // __cpp_lib_ranges_as_const
        | std::views::transform(transformer)
    );
#else
    std::transform(
        adjacency_list.cbegin(),
        adjacency_list.cend(),
        std::inserter(state_list, state_list.begin()),
        transformer
    );
#endif // __cpp_lib_containers_ranges
}

} // namespace forfun::graph

#endif // FORFUN_GRAPH_VERTEX_HPP_
