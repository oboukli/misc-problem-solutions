// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/move_zeroes.hpp"

TEMPLATE_TEST_CASE_SIG(
    "move_zeroes in std::vector",
    "[move_zeroes]",
    ((auto move_zeroes), move_zeroes),
    (forfun::move_zeroes::sol1::move_zeroes<std::vector<int>::iterator>),
    (forfun::move_zeroes::sol2::move_zeroes<std::vector<int>::iterator>),
    (forfun::move_zeroes::stl::move_zeroes<std::vector<int>::iterator>))
{
    auto [test_input, expected]{
        GENERATE(table<std::vector<int>, std::vector<int>>({
            {{}, {}},
            {{-1}, {-1}},
            {{0}, {0}},
            {{1}, {1}},
            {{0, 0}, {0, 0}},
            {{0, 1}, {1, 0}},
            {{1, 0, 0, 3}, {1, 3, 0, 0}},
            {{0, 1, 0, 3, 12}, {1, 3, 12, 0, 0}},
            {{0, 1, 0, -1, 12}, {1, -1, 12, 0, 0}},
            {{0, 11, 0, 13, 2}, {11, 13, 2, 0, 0}},
        }))};

    CAPTURE(test_input);

    move_zeroes(test_input.begin(), test_input.end());

    REQUIRE_THAT(test_input, Catch::Matchers::RangeEquals(expected));
}

TEMPLATE_TEST_CASE_SIG(
    "move_zeroes in std::array",
    "[move_zeroes]",
    ((auto move_zeroes), move_zeroes),
    (forfun::move_zeroes::sol1::move_zeroes<std::array<int, 5>::iterator>),
    (forfun::move_zeroes::sol2::move_zeroes<std::array<int, 5>::iterator>),
    (forfun::move_zeroes::stl::move_zeroes<std::array<int, 5>::iterator>))
{
    constexpr std::array const expected{1, 3, 12, 0, 0};
    std::array<int, 5> test_input{0, 1, 0, 3, 12};

    CAPTURE(test_input);

    move_zeroes(test_input.begin(), test_input.end());

    REQUIRE_THAT(test_input, Catch::Matchers::RangeEquals(expected));
}
