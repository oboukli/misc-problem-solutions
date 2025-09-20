// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_VERTEX_HPP_
#define FORFUN_GRAPH_VERTEX_HPP_

#include <algorithm>
#include <concepts>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace forfun::graph {

enum struct vertex_visit_state : bool {
    unvisited = false,
    visited = true,
};

template <typename V>
    requires std::is_trivially_copyable_v<V>
using vertex_adjacency_list = std::vector<std::vector<V>>;

template <typename V>
    requires std::regular<V> and std::is_trivially_copyable_v<V>
using vertex_state_list = std::unordered_map<V, vertex_visit_state>;

template <typename T>
constexpr auto get_adjacencies_iter(
    vertex_adjacency_list<T> const& adjacency_list, T const v
) noexcept -> vertex_adjacency_list<T>::const_iterator
{
    return std::find_if(
        adjacency_list.cbegin(),
        adjacency_list.cend(),
        [v](vertex_adjacency_list<T>::value_type const& target) noexcept {
            return target.front() == v;
        }
    );
}

template <std::regular T>
auto init_state_list(
    vertex_adjacency_list<T> const& adjacency_list,
    vertex_state_list<T>& state_list
) -> void
{
    for (auto const& adjacencies : adjacency_list)
    {
        state_list.insert({adjacencies.front(), vertex_visit_state::unvisited});
    }
}

} // namespace forfun::graph

#endif // FORFUN_GRAPH_VERTEX_HPP_
