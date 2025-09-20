// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iterator>
#include <sstream>
#include <string_view>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/graph/vertex.hpp"

TEST_CASE("Vertex conversion", "[graph][vertex]")
{
    SECTION("Covert vertex to ostream")
    {
        using std::string_view_literals::operator""sv;

        std::ostringstream buffer{};

        static constexpr forfun::graph::vertex const v{17};
        forfun::graph::operator<<(buffer, v);

        REQUIRE(buffer.str() == "17"sv);
    }
}

TEST_CASE("Get vertex adjacencies iterator", "[graph][get_adjacencies_iter]")
{
    using forfun::graph::vertex;
    using forfun::graph::vertex_adjacency_list;

    SECTION("Empty adjacency list (graph)")
    {
        static constexpr vertex const v{17};
        vertex_adjacency_list<int> const adjacency_list{};

        CAPTURE(v);
        CAPTURE(adjacency_list);

        REQUIRE(
            get_adjacencies_iter(adjacency_list, v) == adjacency_list.cend()
        );
    }

    SECTION("Adjacency list can be found for vertex")
    {
        static constexpr vertex const v{4};
        vertex_adjacency_list<int> const adjacency_list{
            {{1}, {2}, {3}, {4}},
            {{2}, {1}},
            {{3}, {1}},
            {{4}, {1}, {5}},
            {{5}, {4}, {6}},
            {{6}, {5}},
        };

        CAPTURE(v);
        CAPTURE(adjacency_list);

        REQUIRE(
            get_adjacencies_iter(adjacency_list, v)
            == std::next(adjacency_list.cbegin(), 3)
        );
    }

    SECTION("Adjacency list can be found for vertex<std::string>")
    {
        using std::string_view_literals::operator""sv;

        static constexpr vertex const v{"five"sv};
        vertex_adjacency_list<std::string_view> const adjacency_list{
            {{"one"sv}, {"two"sv}, {"three"sv}, {"four"sv}},
            {{"two"sv}, {"one"sv}},
            {{"three"sv}, {"one"sv}},
            {{"four"sv}, {"one"sv}, {"five"sv}},
            {{"five"sv}, {"four"sv}, {"six"sv}},
            {{"six"sv}, {"five"sv}},
        };

        CAPTURE(v);
        CAPTURE(adjacency_list);

        REQUIRE(
            get_adjacencies_iter(adjacency_list, v)
            == std::next(adjacency_list.cbegin(), 4)
        );
    }
}

TEST_CASE("Initialize graph state list", "[graph][init_state_list]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex;
    using forfun::graph::vertex_adjacency_list;
    using forfun::graph::vertex_state_list;
    using forfun::graph::vertex_visit_state;

    SECTION("Empty adjacency list (graph)")
    {
        vertex_adjacency_list<int> const adjacency_list{};
        vertex_state_list<int> state_list{};

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        REQUIRE(state_list.empty());
        REQUIRE(adjacency_list.empty());
    }

    SECTION("Graph state list initialized (int)")
    {
        vertex_adjacency_list<int> const adjacency_list{
            {{1}, {2}, {3}, {4}},
            {{2}, {1}},
            {{3}, {1}},
            {{4}, {1}, {5}},
            {{5}, {4}, {6}},
            {{6}, {5}},
        };
        vertex_state_list<int> state_list{};

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        vertex_state_list<int> const expected_state_list{
            {{1}, vertex_visit_state::unvisited},
            {{2}, vertex_visit_state::unvisited},
            {{3}, vertex_visit_state::unvisited},
            {{4}, vertex_visit_state::unvisited},
            {{5}, vertex_visit_state::unvisited},
            {{6}, vertex_visit_state::unvisited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6UZ);
    }

    SECTION("Graph state list initialized (std::string)")
    {
        using std::string_view_literals::operator""sv;

        vertex_adjacency_list<std::string_view> const adjacency_list{
            {{"one"sv}, {"two"sv}, {"three"sv}, {"four"sv}},
            {{"two"sv}, {"one"sv}},
            {{"three"sv}, {"one"sv}},
            {{"four"sv}, {"one"sv}, {"five"sv}},
            {{"five"sv}, {"four"sv}, {"six"sv}},
            {{"six"sv}, {"five"sv}},
        };
        vertex_state_list<std::string_view> state_list{};

        state_list.reserve(adjacency_list.size());

        CAPTURE(adjacency_list);
        CAPTURE(state_list);

        init_state_list(adjacency_list, state_list);

        vertex_state_list<std::string_view> const expected_state_list{
            {{"one"sv}, vertex_visit_state::unvisited},
            {{"two"sv}, vertex_visit_state::unvisited},
            {{"three"sv}, vertex_visit_state::unvisited},
            {{"four"sv}, vertex_visit_state::unvisited},
            {{"five"sv}, vertex_visit_state::unvisited},
            {{"six"sv}, vertex_visit_state::unvisited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6UZ);
    }
}
