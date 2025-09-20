// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
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

template <typename T, std::invocable<T> Visitor>
auto breadth_first_search_imp(
    vertex_adjacency_list<T> const& adjacency_list,
    vertex_state_list<T>& state_list,
    T const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    state_list[start] = vertex_visit_state::visited;
    step(start);

    auto const adjacencies_iter{get_adjacencies_iter(adjacency_list, start)};

    for (auto const adjacency : *adjacencies_iter)
    {
        if (state_list[adjacency] == vertex_visit_state::unvisited)
        {
            breadth_first_search_imp(
                adjacency_list, state_list, adjacency, step
            );
        }
    }
}

} // namespace detail

template <typename T, std::invocable<T> Visitor>
auto breadth_first_search(
    vertex_adjacency_list<T> const& adjacency_list,
    vertex_state_list<T>& state_list,
    T const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    if (adjacency_list.empty())
    {
        return;
    }

    detail::breadth_first_search_imp(adjacency_list, state_list, start, step);
}

} // namespace recursive

} // namespace forfun::graph::breadth_first_search

#endif // FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
