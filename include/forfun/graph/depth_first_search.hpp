// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Depth-first_search

#ifndef FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
#define FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_

#include <concepts>
#include <iterator>
#include <stack>
#include <utility>

#include "forfun/graph/vertex.hpp"

namespace forfun::graph::depth_first_search {

namespace iterative {

/// @note The function assumes that @p adjacency_list and @p state_list are
/// valid and non-empty, otherwise the behavior of the function is undefined.
template <std::regular Vertex, std::invocable<Vertex> Visitor>
auto depth_first_search(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_state_list<Vertex>& state_list,
    Vertex const start,
    Visitor preorder_step
) noexcept(noexcept(preorder_step(start))) -> void
{
    using offset_type = forfun::graph::vertex_adjacency_list<
        Vertex>::mapped_type::difference_type;

    std::stack<std::pair<Vertex, offset_type>> stack{};
    stack.emplace(start, 0);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        auto const [current_vertex, offset]{stack.top()};
        ++stack.top().second;

        if (std::as_const(state_list).find(current_vertex) == state_list.cend())
        {
            state_list.emplace(current_vertex);
            preorder_step(current_vertex);
        }

        auto const& adjacencies{adjacency_list.find(current_vertex)->second};
        auto const adj_iter{std::next(adjacencies.cbegin(), offset)};
        if (adj_iter == adjacencies.cend())
        {
            stack.pop();

            continue;
        }

        auto const& adjacency{*adj_iter};
        if (std::as_const(state_list).find(adjacency) == state_list.cend())
        {
            stack.emplace(adjacency, 0);
        }
    } while (not stack.empty());
}

} // namespace iterative

namespace recursive {

/// @note The function assumes that @p adjacency_list and @p state_list are
/// valid and non-empty, otherwise the behavior of the function is undefined.
template <std::regular Vertex, std::invocable<Vertex> Visitor>
auto depth_first_search(
    vertex_adjacency_list<Vertex> const& adjacency_list,
    vertex_state_list<Vertex>& state_list,
    Vertex const start,
    Visitor preorder_step
) noexcept(noexcept(preorder_step(start))) -> void
{
    state_list.emplace(start);
    preorder_step(start);

    for (auto const& adjacency : adjacency_list.find(start)->second)
    {
        if (std::as_const(state_list).find(adjacency) == state_list.cend())
        {
            depth_first_search(
                adjacency_list, state_list, adjacency, preorder_step
            );
        }
    }
}

} // namespace recursive

} // namespace forfun::graph::depth_first_search

#endif // FORFUN_GRAPH_DEPTH_FIRST_SEARCH_HPP_
