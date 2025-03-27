// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <cstddef>
#include <vector>

#define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>

#include "forfun/graph/breadth_first_search.hpp"
#include "forfun/graph/vertex.hpp"

CATCH_REGISTER_ENUM(
    forfun::graph::vertex_visit_state,
    forfun::graph::vertex_visit_state::unvisited,
    forfun::graph::vertex_visit_state::visited,
    //
)

TEST_CASE("Depth-first search", "[graph][breadth_first]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex;
    using forfun::graph::vertex_visit_state;
    using forfun::graph::VertexAdjacencyList;
    using forfun::graph::VertexStateList;

    using forfun::graph::breadth_first_search::recursive::breadth_first_search;

    SECTION("Empty adjacency list (graph)")
    {
        VertexAdjacencyList<char> const adjacency_list{};
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'0'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.empty());
        assert(state_list.empty());

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<char>) noexcept -> void {}
        );

        CAPTURE(state_list);

        REQUIRE(state_list.empty());
        REQUIRE(adjacency_list.empty());
    }

    SECTION("Two-vertex graph")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'a'}},
        };
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 2U);
        assert(state_list.size() == 2U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::size_t call_count{};
        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [&call_count](vertex<char>) noexcept { ++call_count; }
        );

        CAPTURE(state_list);

        REQUIRE(call_count == 2U);
    }

    SECTION("All graph vertices visited, starting from leaf vertex")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'1'}, {'2'}, {'3'}, {'4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1'}, {'5'}},
            {{'5'}, {'4'}, {'6'}},
            {{'6'}, {'5'}},
        };
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'1'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 6U);
        assert(state_list.size() == 6U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<char>) noexcept {}
        );

        CAPTURE(state_list);

        VertexStateList<char> const expected_state_list{
            {{'1'}, vertex_visit_state::visited},
            {{'2'}, vertex_visit_state::visited},
            {{'3'}, vertex_visit_state::visited},
            {{'4'}, vertex_visit_state::visited},
            {{'5'}, vertex_visit_state::visited},
            {{'6'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6U);
    }

    SECTION("All graph vertices visited, starting from non-leaf vertex")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'1'}, {'2'}, {'3'}, {'4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1'}, {'5'}},
            {{'5'}, {'4'}, {'6'}},
            {{'6'}, {'5'}},
        };
        VertexStateList<char> state_list{};
        vertex<char> const starting_vertex{'5'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 6U);
        assert(state_list.size() == 6U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<char>) noexcept {}
        );

        CAPTURE(state_list);

        VertexStateList<char> const expected_state_list{
            {{'1'}, vertex_visit_state::visited},
            {{'2'}, vertex_visit_state::visited},
            {{'3'}, vertex_visit_state::visited},
            {{'4'}, vertex_visit_state::visited},
            {{'5'}, vertex_visit_state::visited},
            {{'6'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6U);
    }

    SECTION("All graph vertices (vertex<char>) visited")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'c'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 8U);
        assert(state_list.size() == 8U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [](vertex<char>) noexcept {}
        );

        CAPTURE(state_list);

        VertexStateList<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
            {{'c'}, vertex_visit_state::visited},
            {{'d'}, vertex_visit_state::visited},
            {{'e'}, vertex_visit_state::visited},
            {{'f'}, vertex_visit_state::visited},
            {{'g'}, vertex_visit_state::visited},
            {{'h'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 8U);
    }

    SECTION("Visitor call count is the same as the vertex count")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'h'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 8U);
        assert(state_list.size() == 8U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::size_t call_count{};
        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [&call_count](vertex<char>) noexcept { ++call_count; }
        );

        CAPTURE(state_list);

        REQUIRE(call_count == 8U);
    }

    SECTION("Visitor is called and is passed valid arguments to")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        VertexStateList<char> state_list{};
        constexpr vertex<char> const starting_vertex{'e'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        assert(adjacency_list.size() == 8U);
        assert(state_list.size() == 8U);
        assert(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> recorded_path{};
        recorded_path.reserve(8);

        breadth_first_search(
            adjacency_list,
            state_list,
            starting_vertex,
            [&recorded_path](vertex<char> v) noexcept {
                recorded_path.emplace_back(v);
            }
        );

        CAPTURE(state_list);

        REQUIRE(recorded_path.size() == 8U);

        std::vector<vertex<char>> const expected_recorded_path{
            {{'e'}, {'d'}, {'a'}, {'b'}, {'c'}, {'f'}, {'h'}, {'g'}}
        };
        REQUIRE(recorded_path == expected_recorded_path);
    }
}
