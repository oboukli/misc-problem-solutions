// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_GRAPH_VERTEX_HPP_
#define FORFUN_GRAPH_VERTEX_HPP_

#include <concepts>
#include <cstddef>
#include <functional>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace forfun::graph {

enum class vertex_visit_state : bool {
    unvisited = false,
    visited = true,
};

template <std::regular V>
struct vertex {
    V value{};
    constexpr auto operator==(vertex<V> const&) const -> bool = default;
};

template <std::regular T>
struct vertex_hash {
    constexpr auto
    operator()(vertex<T> const& vertex) const noexcept -> std::size_t
    {
        if constexpr (sizeof(T) <= sizeof(std::size_t))
        {
            return static_cast<std::size_t>(vertex.value);
        }

        return std::hash<T>{}(vertex.value);
    }
};

template <std::regular T>
using VertexAdjacencyList = std::vector<std::vector<vertex<T>>>;

template <std::regular T>
using VertexStateList
    = std::unordered_map<vertex<T>, vertex_visit_state, vertex_hash<T>>;

template <std::regular T>
constexpr auto get_adjacencies_iter(
    VertexAdjacencyList<T> const& vertex_adjacency_list,
    vertex<T> const& v) noexcept -> VertexAdjacencyList<T>::const_iterator
{
    return std::find_if(
        vertex_adjacency_list.cbegin(),
        vertex_adjacency_list.cend(),
        [v](VertexAdjacencyList<T>::value_type const& target) {
            return target.front() == v;
        });
}

template <std::regular T>
auto init_state_list(
    VertexAdjacencyList<T> const& adjacency_list,
    VertexStateList<T>& state_list) noexcept -> void
{
    for (auto const& adjacencies : adjacency_list)
    {
        state_list.insert({adjacencies.front(), vertex_visit_state::unvisited});
    }
}

template <std::regular T>
    requires requires(std::ostream os, vertex<T> v) {
        { os << v.value } -> std::convertible_to<std::ostream&>;
    }
auto operator<<(std::ostream& os, vertex<T> const& v) -> std::ostream&
{
    os << v.value;

    return os;
}

} // namespace forfun::graph

#endif // FORFUN_GRAPH_VERTEX_HPP_
