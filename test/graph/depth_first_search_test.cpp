// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <vector>
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/depth_first_search.hpp"
#include "forfun/graph/vertex.hpp"

TEST_CASE("Depth-first search", "[graph][depth_first]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex;
    using forfun::graph::vertex_visit_state;
    using forfun::graph::VertexAdjacencyList;
    using forfun::graph::VertexStateList;

    using forfun::graph::depth_first_search::recursive::depth_first_search;

    SECTION("Empty adjacency list (graph)")
    {
        VertexAdjacencyList<int> const adjacency_list{};
        VertexStateList<int> state_list{};
        constexpr vertex<int> const starting_vertex{0};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.empty());
        assert(state_list.empty());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);
        CAPTURE(starting_vertex);

        depth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<int>) noexcept -> void {});

        REQUIRE(state_list.empty());
        REQUIRE(adjacency_list.empty());
    }

    SECTION("All graph vertices visited")
    {
        VertexAdjacencyList<int> const adjacency_list{
            // clang-format off
            {{1}, {2}, {3}, {4},},
            {{2},},
            {{3},},
            {{4}, {5},},
            {{5}, {6},},
            {{6},},
            // clang-format on
        };
        VertexStateList<int> state_list{};
        constexpr vertex<int> const starting_vertex{1};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 6);
        assert(state_list.size() == 6);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(state_list);
        CAPTURE(starting_vertex);

        depth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<int>) noexcept {});

        VertexStateList<int> const expected_state_list{
            // clang-format off
            {{1}, vertex_visit_state::visited},
            {{2}, vertex_visit_state::visited},
            {{3}, vertex_visit_state::visited},
            {{4}, vertex_visit_state::visited},
            {{5}, vertex_visit_state::visited},
            {{6}, vertex_visit_state::visited},
            // clang-format on
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6);
    }
}
