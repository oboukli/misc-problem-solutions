// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Breadth-first_search

#ifndef FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
#define FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_

#include <concepts>

#include "forfun/graph/vertex.hpp"

namespace forfun::graph::breadth_first_search {

namespace iterative {
// Placeholder.
} // namespace iterative

namespace recursive {

namespace detail {

template <typename T, std::invocable<vertex<T>> Visitor>
constexpr auto breadth_first_search_imp(
    VertexAdjacencyList<T> const& vertex_adjacency_list,
    VertexStateList<T>& vertex_state_list,
    vertex<T> const& start,
    Visitor const step) noexcept(noexcept(step(start))) -> void
{
    vertex_state_list[start] = vertex_visit_state::visited;
    step(start);

    auto const adjacencies_iter{
        get_adjacencies_iter(vertex_adjacency_list, start)};

    for (auto const adjacency : *adjacencies_iter)
    {
        if (vertex_state_list[adjacency] == vertex_visit_state::unvisited)
        {
            breadth_first_search_imp(
                vertex_adjacency_list, vertex_state_list, adjacency, step);
        }
    }
}

} // namespace detail

template <typename T, std::invocable<vertex<T>> Visitor>
constexpr auto breadth_first_search(
    VertexAdjacencyList<T> const& vertex_adjacency_list,
    VertexStateList<T>& vertex_state_list,
    vertex<T> const& start,
    Visitor const step) noexcept(noexcept(step(start))) -> void
{
    if (vertex_adjacency_list.empty())
    {
        return;
    }

    detail::breadth_first_search_imp(
        vertex_adjacency_list, vertex_state_list, start, step);
}

} // namespace recursive

} // namespace forfun::graph::breadth_first_search

#endif // FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
