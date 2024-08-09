// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/graph/breadth_first_search.hpp"
#include "forfun/graph/vertex.hpp"

TEST_CASE(
    "Breadth-first search benchmarking",
    "[benchmark][graph][breadth_first_search]"
)
{
    using namespace forfun::graph::breadth_first_search;

    using forfun::graph::vertex;
    using forfun::graph::vertex_visit_state;
    using forfun::graph::VertexAdjacencyList;
    using forfun::graph::VertexStateList;

    using Visitor = decltype([](vertex<int>) noexcept -> void {});

    VertexAdjacencyList<int> const adjacency_list{
        {{1}, {2}, {3}, {4}},
        {{2}, {1}},
        {{3}, {1}},
        {{4}, {1}, {5}},
        {{5}, {4}, {6}},
        {{6}, {5}},
    };

    ankerl::nanobench::Bench()

        .title("Breadth-first search")
        .relative(true)

        .run(
            NAMEOF_RAW(recursive::breadth_first_search<int, Visitor>).c_str(),
            [&adjacency_list]() {
                constexpr vertex<int> const starting_vertex{1};

                VertexStateList<int> state_list{
                    {{1}, vertex_visit_state::unvisited},
                    {{2}, vertex_visit_state::unvisited},
                    {{3}, vertex_visit_state::unvisited},
                    {{4}, vertex_visit_state::unvisited},
                    {{5}, vertex_visit_state::unvisited},
                    {{6}, vertex_visit_state::unvisited},
                };

                recursive::breadth_first_search(
                    adjacency_list,
                    state_list,
                    starting_vertex,
                    [](vertex<int>) noexcept -> void {}
                );
                ankerl::nanobench::doNotOptimizeAway(state_list);
            }
        )

        ;
}
