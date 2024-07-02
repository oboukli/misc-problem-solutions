// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Depth-first_search

#ifndef FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
#define FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_

#include <algorithm>
#include <concepts>

#include "forfun/graph/vertex.hpp"

namespace forfun::graph::depth_first_search {

namespace iterative {

// Placeholder.

} // namespace iterative

namespace recursive {

namespace detail {

template <std::regular T, std::invocable<vertex<T>> Visitor>
constexpr auto depth_first_search_imp(
    VertexAdjacencyList<T> const& vertex_adjacency_list,
    VertexStateList<T>& vertex_state_list,
    vertex<T> const& start,
    Visitor const preorder_step) noexcept(noexcept(preorder_step(start)))
    -> void
{
    vertex_state_list[start] = vertex_visit_state::visited;
    preorder_step(start);

    auto const adjacencies_iter{
        get_adjacencies_iter(vertex_adjacency_list, start)};

    auto itr{adjacencies_iter->cbegin()};
    auto const end{adjacencies_iter->cend()};

    for (; itr != end; ++itr)
    {
        if (auto const adjacency = *itr;
            vertex_state_list[adjacency] == vertex_visit_state::unvisited)
        {
            depth_first_search_imp(
                vertex_adjacency_list,
                vertex_state_list,
                adjacency,
                preorder_step);
        }
    }
}

} // namespace detail

template <std::regular T, std::invocable<vertex<T>> Visitor>
constexpr auto depth_first_search(
    VertexAdjacencyList<T> const& vertex_adjacency_list,
    VertexStateList<T>& vertex_state_list,
    vertex<T> const& start,
    Visitor const preorder_step) noexcept(noexcept(preorder_step(start)))
    -> void
{
    if (vertex_adjacency_list.empty())
    {
        return;
    }

    detail::depth_first_search_imp(
        vertex_adjacency_list, vertex_state_list, start, preorder_step);
}

} // namespace recursive

} // namespace forfun::graph::depth_first_search

#endif // FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
