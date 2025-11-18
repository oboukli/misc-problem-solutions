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
    vertex_state_list<Vertex>& state_list,
    Vertex const start,
    Visitor step
) noexcept(noexcept(step(start))) -> void
{
    std::deque<Vertex> to_visit{};
    for (auto const& adjacency : adjacency_list.find(start)->second)
    {
        if (std::as_const(state_list).find(adjacency) == state_list.cend())
        {
            state_list.emplace(adjacency);
            step(adjacency);

            to_visit.emplace_back(adjacency);
        }
    }

    for (auto const vertex : to_visit)
    {
        do_breadth_first_search_(adjacency_list, state_list, vertex, step);
    }
}

} // namespace detail

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
    state_list.emplace(start);
    step(start);

    detail::do_breadth_first_search_(adjacency_list, state_list, start, step);
}

} // namespace recursive

} // namespace forfun::graph::breadth_first_search

#endif // FORFUN_GRAPH_BREADTH_FIRST_SEARCH_HPP_
