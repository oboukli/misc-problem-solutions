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
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace forfun::graph {

enum struct vertex_visit_state : bool {
    unvisited = false,
    visited = true,
};

template <std::regular V>
struct vertex final {
    V value{};
    constexpr auto operator==(vertex const&) const -> bool = default;
};

template <typename T>
struct vertex_hash final {
    constexpr auto operator()(vertex<T> const& vertex) const noexcept
        -> std::size_t
    {
        if constexpr (std::integral<T> and (sizeof(T) <= sizeof(std::size_t)))
        {
            return static_cast<std::size_t>(vertex.value);
        }
        else
        {
            return std::hash<T>{}(vertex.value);
        }
    }
};

template <typename V>
    requires std::is_trivially_copyable_v<V>
using vertex_adjacency_list = std::vector<std::vector<vertex<V>>>;

template <typename V>
    requires std::is_trivially_copyable_v<V>
using vertex_state_list
    = std::unordered_map<vertex<V>, vertex_visit_state, vertex_hash<V>>;

template <std::regular T>
constexpr auto get_adjacencies_iter(
    vertex_adjacency_list<T> const& adjacency_list, vertex<T> const& v
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
