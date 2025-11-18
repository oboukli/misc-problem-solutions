// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/graph/breadth_first_search.hpp"
#include "forfun/graph/vertex.hpp"

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

TEST_CASE("Breadth-first search", "[graph][breadth_first_search]")
{
    using forfun::graph::vertex_adjacency_list;
    using forfun::graph::vertex_visit_state;

    using forfun::graph::breadth_first_search::recursive::breadth_first_search;

    SECTION("One-vertex acyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{{'a', {}}};
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'a'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 1UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{'a'};

        static constexpr std::array const expected_visit_log{'a'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("One-vertex cyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{{'a', {'a'}}};
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'a'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 1UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{'a'};

        static constexpr std::array const expected_visit_log{'a'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Two-vertex acyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {}},
            {'b', {'a'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'b'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 2UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
        };

        static constexpr std::array const expected_visit_log{'b', 'a'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Two-vertex cyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b'}},
            {'b', {'a'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'a'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 2UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
        };

        static constexpr std::array const expected_visit_log{'a', 'b'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex acyclic graph (case 1)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b'}},
            {'b', {'c'}},
            {'c', {}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'a'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 3UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
            'c',
        };

        static constexpr std::array const expected_visit_log{'a', 'b', 'c'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex acyclic graph (case 2)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b'}},
            {'b', {'c'}},
            {'c', {}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'b'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 3UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'b',
            'c',
        };

        static constexpr std::array const expected_visit_log{'b', 'c'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("Three-vertex cyclic graph")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b'}},
            {'b', {'c'}},
            {'c', {'a'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'b'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 3UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
            'c',
        };

        static constexpr std::array const expected_visit_log{'b', 'c', 'a'};

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 1)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'1', {'2', '3', '4'}},
            {'2', {'1'}},
            {'3', {'1'}},
            {'4', {'1', '5'}},
            {'5', {'4', '6'}},
            {'6', {'5'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'1'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 6UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
        };

        static constexpr std::array const expected_visit_log{
            '1', '2', '3', '4', '5', '6'
        };

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 2)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'1', {'2', '3', '4'}},
            {'2', {'1'}},
            {'3', {'1'}},
            {'4', {'1', '5'}},
            {'5', {'4', '6'}},
            {'6', {'5'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'5'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 6UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
        };

        static constexpr std::array const expected_visit_log{
            '5', '4', '6', '1', '2', '3'
        };

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 3)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b', 'c', 'd'}},
            {'b', {'a'}},
            {'c', {'a'}},
            {'d', {'a', 'e'}},
            {'e', {'d', 'f', 'g'}},
            {'f', {'e', 'h'}},
            {'g', {'e', 'h'}},
            {'h', {'f', 'g'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'c'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 8UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
            'c',
            'd',
            'e',
            'f',
            'g',
            'h',
        };

        static constexpr std::array const expected_visit_log{
            'c', 'a', 'b', 'd', 'e', 'f', 'g', 'h'
        };

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 4)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b', 'c', 'd'}},
            {'b', {'a'}},
            {'c', {'a'}},
            {'d', {'a', 'e'}},
            {'e', {'d', 'f', 'g'}},
            {'f', {'e', 'h'}},
            {'g', {'e', 'h'}},
            {'h', {'f', 'g'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'h'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 8UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
            'c',
            'd',
            'e',
            'f',
            'g',
            'h',
        };

        static constexpr std::array const expected_visit_log{
            'h', 'f', 'g', 'e', 'd', 'a', 'b', 'c'
        };

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }

    SECTION("All graph vertices visited (case 5)")
    {
        vertex_adjacency_list<char> const adjacency_list{
            {'a', {'b', 'c', 'd'}},
            {'b', {'a'}},
            {'c', {'a'}},
            {'d', {'a', 'e'}},
            {'e', {'d', 'f', 'g'}},
            {'f', {'e', 'h'}},
            {'g', {'e', 'h'}},
            {'h', {'f', 'g'}},
        };
        vertex_visit_state<char> visit_state{};
        static constexpr auto const starting_vertex{'e'};

        visit_state.reserve(adjacency_list.size());

        CHECK(adjacency_list.size() == 8UZ);

        CAPTURE(adjacency_list);
        CAPTURE(starting_vertex);

        std::vector<char> visit_log{};
        visit_log.reserve(adjacency_list.size());
        VisitRecorder const visit_recorder(&visit_log);

        breadth_first_search(
            adjacency_list, visit_state, starting_vertex, visit_recorder
        );

        CAPTURE(visit_state);

        vertex_visit_state<char> const expected_state_list{
            'a',
            'b',
            'c',
            'd',
            'e',
            'f',
            'g',
            'h',
        };

        static constexpr std::array const expected_visit_log{
            'e', 'd', 'f', 'g', 'a', 'b', 'c', 'h'
        };

        REQUIRE(visit_state == expected_state_list);
        REQUIRE_THAT(
            visit_log, Catch::Matchers::RangeEquals(expected_visit_log)
        );
    }
}
