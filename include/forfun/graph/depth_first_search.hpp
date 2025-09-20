// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Depth-first_search

#ifndef FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
#define FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_

#include <concepts>

#include "forfun/graph/vertex.hpp"

namespace forfun::graph::depth_first_search {

namespace iterative {

// Placeholder.

} // namespace iterative

namespace recursive {

namespace detail {

template <std::regular T, std::invocable<vertex<T>> Visitor>
auto depth_first_search_imp(
    VertexAdjacencyList<T> const& adjacency_list,
    VertexStateList<T>& state_list,
    vertex<T> const& start,
    Visitor preorder_step
) noexcept(noexcept(preorder_step(start))) -> void
{
    state_list[start] = vertex_visit_state::visited;
    preorder_step(start);

    auto const adj_iter{get_adjacencies_iter(adjacency_list, start)};

    for (auto iter{adj_iter->cbegin()}; iter != adj_iter->cend(); ++iter)
    {
        if (auto const adjacency{*iter};
            state_list[adjacency] == vertex_visit_state::unvisited)
        {
            depth_first_search_imp(
                adjacency_list, state_list, adjacency, preorder_step
            );
        }
    }
}

} // namespace detail

template <std::regular T, std::invocable<vertex<T>> Visitor>
auto depth_first_search(
    VertexAdjacencyList<T> const& adjacency_list,
    VertexStateList<T>& state_list,
    vertex<T> const& start,
    Visitor preorder_step
) noexcept(noexcept(preorder_step(start))) -> void
{
    if (adjacency_list.empty())
    {
        return;
    }

    detail::depth_first_search_imp(
        adjacency_list, state_list, start, preorder_step
    );
}

} // namespace recursive

} // namespace forfun::graph::depth_first_search

#endif // FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
