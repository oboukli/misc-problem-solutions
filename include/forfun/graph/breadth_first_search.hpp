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

/// @note The function assumes that @p adjacency_list and @p state_list are
/// valid and non-empty, otherwise the behavior of the function is undefined.
template <typename Vertex, std::invocable<Vertex> Visitor>
auto breadth_first_search(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_state_list<Vertex>& state_list,
    Vertex const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    state_list.find(start)->second = vertex_visit_state::visited;
    step(start);

    for (auto const& adjacency : adjacency_list.find(start)->second)
    {
        if (state_list.find(adjacency)->second == vertex_visit_state::unvisited)
        {
            breadth_first_search(adjacency_list, state_list, adjacency, step);
        }
    }
}

} // namespace recursive

} // namespace forfun::graph::breadth_first_search

#endif // FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
