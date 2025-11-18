// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Breadth-first_search

#ifndef FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
#define FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_

#include <concepts>
#include <deque>
#include <utility>

#include "forfun/graph/vertex.hpp"

namespace forfun::graph::breadth_first_search {

namespace iterative {

// Placeholder.

} // namespace iterative

namespace recursive {

namespace detail {

template <typename Vertex, std::invocable<Vertex> Visitor>
auto do_breadth_first_search_(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_visit_state<Vertex>& visit_state,
    Vertex const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    std::deque<Vertex> to_visit{};
    for (auto const& adjacency : adjacency_list.find(start)->second)
    {
        if (std::as_const(visit_state).find(adjacency) == visit_state.cend())
        {
            visit_state.emplace(adjacency);
            step(adjacency);

            to_visit.emplace_back(adjacency);
        }
    }

    for (auto const vertex : to_visit)
    {
        do_breadth_first_search_(adjacency_list, visit_state, vertex, step);
    }
}

} // namespace detail

/// @note The function assumes that @p adjacency_list and @p visit_state are
/// valid and non-empty, otherwise the behavior of the function is undefined.
template <typename Vertex, std::invocable<Vertex> Visitor>
auto breadth_first_search(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_visit_state<Vertex>& visit_state,
    Vertex const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    visit_state.emplace(start);
    step(start);

    detail::do_breadth_first_search_(adjacency_list, visit_state, start, step);
}

} // namespace recursive

} // namespace forfun::graph::breadth_first_search

#endif // FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
