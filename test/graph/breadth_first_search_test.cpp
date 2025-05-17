// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

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

namespace {

class VisitRecorder final {
public:
    explicit VisitRecorder(
        std::vector<forfun::graph::vertex<char>>* const visits
    ) noexcept :
        visits_{visits}
    {
    }

    auto operator()(forfun::graph::vertex<char> const v) noexcept -> void
    {
        visits_->emplace_back(v);
    }

private:
    std::vector<forfun::graph::vertex<char>>* visits_{};
};

} // namespace

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
        static constexpr vertex<char> const starting_vertex{'0'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.empty());
        CHECK(state_list.empty());

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(0U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        REQUIRE(adjacency_list.empty());
        REQUIRE(state_list.empty());
        REQUIRE(visits.size() == 0ZU);
    }

    SECTION("One-vertex graph")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}},
        };
        VertexStateList<char> state_list{};
        static constexpr vertex<char> const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 1U);
        CHECK(state_list.size() == 1U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(1U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        VertexStateList<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited}
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 1ZU);
    }

    SECTION("Two-vertex graph")
    {
        VertexAdjacencyList<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'a'}},
        };
        VertexStateList<char> state_list{};
        static constexpr vertex<char> const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 2U);
        CHECK(state_list.size() == 2U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(2U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        VertexStateList<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
        };

        REQUIRE(visits.size() == 2ZU);
        REQUIRE(state_list == expected_state_list);
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
        static constexpr vertex<char> const starting_vertex{'1'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 6U);
        CHECK(state_list.size() == 6U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(6U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
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

        REQUIRE(adjacency_list.size() == 6U);
        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 6ZU);
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
        static constexpr vertex<char> const starting_vertex{'5'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 6U);
        CHECK(state_list.size() == 6U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(6U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
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

        REQUIRE(adjacency_list.size() == 6U);
        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 6ZU);
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
        static constexpr vertex<char> const starting_vertex{'c'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8U);
        CHECK(state_list.size() == 8U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(8U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
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

        REQUIRE(adjacency_list.size() == 8U);
        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 8ZU);
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
        static constexpr vertex<char> const starting_vertex{'h'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8U);
        CHECK(state_list.size() == 8U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(8U);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
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
        REQUIRE(visits.size() == 8ZU);
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
        static constexpr vertex<char> const starting_vertex{'e'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8U);
        CHECK(state_list.size() == 8U);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<vertex<char>> visits{};
        visits.reserve(8);
        VisitRecorder visit_recorder(&visits);

        breadth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        REQUIRE(visits.size() == 8U);

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

        std::vector<vertex<char>> const expected_visits{
            {{'e'}, {'d'}, {'a'}, {'b'}, {'c'}, {'f'}, {'h'}, {'g'}}
        };

        REQUIRE(visits == expected_visits);
        REQUIRE(state_list == expected_state_list);
    }
}
