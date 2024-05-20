// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/vertex.hpp"

TEST_CASE("Initialize graph state list", "[graph][init_state_list]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex;
    using forfun::graph::vertex_visit_state;
    using forfun::graph::VertexAdjacencyList;
    using forfun::graph::VertexStateList;

    SECTION("Empty adjacency list (graph)")
    {
        VertexAdjacencyList<int> const adjacency_list{};
        VertexStateList<int> state_list{};

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        REQUIRE(state_list.empty());
        REQUIRE(adjacency_list.empty());
    }

    SECTION("Graph state list initialized (int)")
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

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        VertexStateList<int> const expected_state_list{
            // clang-format off
            {{1}, vertex_visit_state::unvisited},
            {{2}, vertex_visit_state::unvisited},
            {{3}, vertex_visit_state::unvisited},
            {{4}, vertex_visit_state::unvisited},
            {{5}, vertex_visit_state::unvisited},
            {{6}, vertex_visit_state::unvisited},
            // clang-format on
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6);
    }

    SECTION("Graph state list initialized (std::string)")
    {
        using std::literals::string_literals::operator""s;

        VertexAdjacencyList<std::string> const adjacency_list{
            // clang-format off
            {{"one"s}, {"two"s}, {"three"s}, {"four"s},},
            {{"two"s},},
            {{"three"s},},
            {{"four"s}, {"five"s},},
            {{"five"s}, {"six"s},},
            {{"six"s},},
            // clang-format on
        };
        VertexStateList<std::string> state_list{};

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        VertexStateList<std::string> const expected_state_list{
            // clang-format off
            {{"one"s}, vertex_visit_state::unvisited},
            {{"two"s}, vertex_visit_state::unvisited},
            {{"three"s}, vertex_visit_state::unvisited},
            {{"four"s}, vertex_visit_state::unvisited},
            {{"five"s}, vertex_visit_state::unvisited},
            {{"six"s}, vertex_visit_state::unvisited},
            // clang-format on
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6);
    }
}
