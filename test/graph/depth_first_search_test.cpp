// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_tostring.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

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
    explicit VisitRecorder(std::vector<char>* const visit_log) noexcept :
        visit_log_{visit_log}
    {
    }

    auto operator()(char const v) const noexcept -> void
    {
        visit_log_->emplace_back(v);
    }

private:
    std::vector<char>* visit_log_{};
};

} // namespace

TEST_CASE("Depth-first search", "[graph][depth_first_search]")
{
    using forfun::graph::init_state_list;
    using forfun::graph::vertex_adjacency_list;
    using forfun::graph::vertex_state_list;
    using forfun::graph::vertex_visit_state;

    using forfun::graph::depth_first_search::recursive::depth_first_search;

    SECTION("One-vertex acyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{{{'a'}, {}}};
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 1UZ);
        CHECK(state_list.size() == 1UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited}
        };

        static constexpr std::array const expected_visit_log{'a'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("One-vertex cyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{{{'a'}, {'a'}}};
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 1UZ);
        CHECK(state_list.size() == 1UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited}
        };

        static constexpr std::array const expected_visit_log{'a'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Two-vertex acyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {}},
            {{'b'}, {'a'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'b'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 2UZ);
        CHECK(state_list.size() == 2UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
        };

        static constexpr std::array const expected_visit_log{'b', 'a'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Two-vertex cyclic graph")
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
        };

        static constexpr std::array const expected_visit_log{'a', 'b'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex acyclic graph (case 1)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'c'}},
            {{'c'}, {}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'a'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 3UZ);
        CHECK(state_list.size() == 3UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
            {{'c'}, vertex_visit_state::visited},
        };

        static constexpr std::array const expected_visit_log{'a', 'b', 'c'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex acyclic graph (case 2)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'c'}},
            {{'c'}, {}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'b'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 3UZ);
        CHECK(state_list.size() == 3UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::unvisited},
            {{'b'}, vertex_visit_state::visited},
            {{'c'}, vertex_visit_state::visited},
        };

        static constexpr std::array const expected_visit_log{'b', 'c'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex cyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b'}},
            {{'b'}, {'c'}},
            {{'c'}, {'a'}},
        };
        vertex_state_list<char> state_list{};
        static constexpr auto const starting_vertex{'b'};

        state_list.reserve(adjacency_list.size());
        init_state_list(adjacency_list, state_list);

        CHECK(adjacency_list.size() == 3UZ);
        CHECK(state_list.size() == 3UZ);
        CHECK(state_list.at(starting_vertex) == vertex_visit_state::unvisited);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        depth_first_search(
            adjacency_list, state_list, starting_vertex, visit_recorder
        );

        CAPTURE(state_list);

        vertex_state_list<char> const expected_state_list{
            {{'a'}, vertex_visit_state::visited},
            {{'b'}, vertex_visit_state::visited},
            {{'c'}, vertex_visit_state::visited},
        };

        static constexpr std::array const expected_visit_log{'b', 'c', 'a'};

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 1)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'1'}, {'2', '3', '4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1', '5'}},
            {{'5'}, {'4', '6'}},
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

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

        static constexpr std::array const expected_visit_log{
            '1', '2', '3', '4', '5', '6'
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 2)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'1'}, {'2', '3', '4'}},
            {{'2'}, {'1'}},
            {{'3'}, {'1'}},
            {{'4'}, {'1', '5'}},
            {{'5'}, {'4', '6'}},
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

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

        static constexpr std::array const expected_visit_log{
            '5', '4', '1', '2', '3', '6'
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 3)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b', 'c', 'd'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a', 'e'}},
            {{'e'}, {'d', 'f', 'g'}},
            {{'f'}, {'e', 'h'}},
            {{'g'}, {'e', 'h'}},
            {{'h'}, {'f', 'g'}},
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

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

        static constexpr std::array const expected_visit_log{
            'c', 'a', 'b', 'd', 'e', 'f', 'h', 'g'
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 4)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b', 'c', 'd'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a', 'e'}},
            {{'e'}, {'d', 'f', 'g'}},
            {{'f'}, {'e', 'h'}},
            {{'g'}, {'e', 'h'}},
            {{'h'}, {'f', 'g'}},
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

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

        static constexpr std::array const expected_visit_log{
            'h', 'f', 'e', 'd', 'a', 'b', 'c', 'g'
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 5)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {{'a'}, {'b', 'c', 'd'}},
            {{'b'}, {'a'}},
            {{'c'}, {'a'}},
            {{'d'}, {'a', 'e'}},
            {{'e'}, {'d', 'f', 'g'}},
            {{'f'}, {'e', 'h'}},
            {{'g'}, {'e', 'h'}},
            {{'h'}, {'f', 'g'}},
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

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

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

        static constexpr std::array const expected_visit_log{
            'e', 'd', 'a', 'b', 'c', 'f', 'h', 'g'
        };

        REQUIRE(state_list == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }
}
