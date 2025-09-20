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

#include "forfun/graph/depth_first_search.hpp"
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
    explicit VisitRecorder(std::vector<char>* const visits) noexcept :
        visits_{visits}
    {
    }

    auto operator()(char const v) const noexcept -> void
    {
        visits_->emplace_back(v);
    }

private:
    std::vector<char>* visits_{};
};

} // namespace

TEST_CASE("Depth-first search", "[graph][depth_first]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex_adjacency_list;
    using forfun::graph::vertex_state_list;
    using forfun::graph::vertex_visit_state;

    using forfun::graph::depth_first_search::recursive::depth_first_search;

    SECTION("One-vertex graph")
    {
        vertex_adjacency_list<char> const adjacency_list{{{'a'}}};
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 1UZ);
        CHECK(state_list.size() == 1UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(1U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited}
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 1UZ);
    }

    SECTION("Two-vertex graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'a'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 2UZ);
        CHECK(state_list.size() == 2UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(2U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 2UZ);
    }

    SECTION("All graph vertices visited, starting from leaf vertex")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'1'}, {'2'}, {'3'}, {'4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1'}, {'5'}},
            {{'5'}, {'4'}, {'6'}},
            {{'6'}, {'5'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'1'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 6UZ);
        CHECK(state_list.size() == 6UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(6U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'1'}, vertex_visit_state::visited},
            {{'2'}, vertex_visit_state::visited},
            {{'3'}, vertex_visit_state::visited},
            {{'4'}, vertex_visit_state::visited},
            {{'5'}, vertex_visit_state::visited},
            {{'6'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6UZ);
        REQUIRE(visits.size() == 6UZ);
    }

    SECTION("All graph vertices visited, starting from non-leaf vertex")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'1'}, {'2'}, {'3'}, {'4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1'}, {'5'}},
            {{'5'}, {'4'}, {'6'}},
            {{'6'}, {'5'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'5'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 6UZ);
        CHECK(state_list.size() == 6UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(6U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'1'}, vertex_visit_state::visited},
            {{'2'}, vertex_visit_state::visited},
            {{'3'}, vertex_visit_state::visited},
            {{'4'}, vertex_visit_state::visited},
            {{'5'}, vertex_visit_state::visited},
            {{'6'}, vertex_visit_state::visited},
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(adjacency_list.size() == 6UZ);
    }

    SECTION("All graph vertices (char) visited")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'c'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8UZ);
        CHECK(state_list.size() == 8UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(8U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
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
        REQUIRE(adjacency_list.size() == 8UZ);
        REQUIRE(visits.size() == 8UZ);
    }

    SECTION("Visitor call count is the same as the vertex count")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'h'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8UZ);
        CHECK(state_list.size() == 8UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(8U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
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
        REQUIRE(visits.size() == 8UZ);
    }

    SECTION("Visitor is called and is passed valid arguments to")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}, {'c'}, {'d'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a'}, {'e'}},
            {{'e'}, {'d'}, {'f'}, {'g'}},
            {{'f'}, {'e'}, {'h'}},
            {{'g'}, {'e'}, {'h'}},
            {{'h'}, {'f'}, {'g'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'e'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 8UZ);
        CHECK(state_list.size() == 8UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visits{};
        visits.reserve(8U);
        VisitRecorder const visit_recorder(&visits);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
            {{'c'}, vertex_visit_state::visited},
            {{'d'}, vertex_visit_state::visited},
            {{'e'}, vertex_visit_state::visited},
            {{'f'}, vertex_visit_state::visited},
            {{'g'}, vertex_visit_state::visited},
            {{'h'}, vertex_visit_state::visited},
        };

        std::vector<char> const expected_recorded_path{
            {{'e'}, {'d'}, {'a'}, {'b'}, {'c'}, {'f'}, {'h'}, {'g'}}
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE(visits.size() == 8UZ);
        REQUIRE(visits == expected_recorded_path);
    }
}
