// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/set_matrix_zeroes.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Set matrix zeros",
    "[matrix][set_matrix_zeroes]",
    ((auto set_zeroes), set_zeroes),
    (forfun::set_matrix_zeroes::iterator_based_sol1::set_zeroes),
    (forfun::set_matrix_zeroes::iterator_based_sol2::set_zeroes),
    (forfun::set_matrix_zeroes::offset_based::set_zeroes))
{
    SECTION("Invalid matrices")
    {
        auto [matrix, expected]{GENERATE(
            table<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(
                {
                    {{}, {}},
                    {{{}}, {{}}},
                }))};

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("One-element matrices")
    {
        auto [matrix, expected]{GENERATE(
            table<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(
                {
                    {{{0}}, {{0}}},
                    {{{1}}, {{1}}},
                }))};

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two-by-two matrices")
    {
        auto [matrix, expected]{GENERATE(
            table<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(
                {
                    // clang-format off
                    {
                        {
                            {0, 0},
                            {0, 0},
                        },
                        {
                            {0, 0},
                            {0, 0},
                        },
                    },
                    {
                        {
                            {0, 1},
                            {1, 0},
                        },
                        {
                            {0, 0},
                            {0, 0},
                        },
                    },
                    {
                        {
                            {1, 0},
                            {0, 1},
                        },
                        {
                            {0, 0},
                            {0, 0},
                        },
                    },
                    {
                        {
                            {1, 1},
                            {1, 1},
                        },
                        {
                            {1, 1},
                            {1, 1},
                        },
                    },
                    // clang-format on
                }))};

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-three matrices")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            { 2,  3,  5},
            { 7, 11, 13},
            {17, 19, 23},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            { 2,  3,  5},
            { 7, 11, 13},
            {17, 19, 23},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-three matrix (LeetCode test case 1)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {1, 1, 1},
            {1, 0, 1},
            {1, 1, 1},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {1, 0, 1},
            {0, 0, 0},
            {1, 0, 1},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-four matrix (LeetCode test case 2)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 3, 1, 5},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0, 0},
            {0, 4, 5, 0},
            {0, 3, 1, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-four matrix (case 1)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 0, 1, 5},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0, 0},
            {0, 0, 5, 0},
            {0, 0, 0, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-four matrix (case 2)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 0, 1, 5},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0, 0},
            {0, 0, 5, 0},
            {0, 0, 0, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three-by-four matrix (case 3)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 1, 2, 0},
            {3, 4, 5, 2},
            {1, 0, 0, 5},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Four-by-three matrix (case 1)")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 1, 2},
            {3, 4, 5},
            {1, 0, 1},
            {1, 0, 1},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0},
            {0, 0, 5},
            {0, 0, 0},
            {0, 0, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Four-by-four matrix")
    {
        std::vector<std::vector<int>> matrix{
            // clang-format off
            {0, 2, 3, 0},
            {5, 7, 2, 3},
            {5, 2, 0, 0},
            {5, 2, 7, 0},
            // clang-format on
        };

        std::vector<std::vector<int>> expected{
            // clang-format off
            {0, 0, 0, 0},
            {0, 7, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            // clang-format on
        };

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Eighteen-by-sixteen matrix (benchmark case)")
    {
        // clang-format off
        std::vector<std::vector<int>> matrix{
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        };
        // clang-format on

        // clang-format off
        std::vector<std::vector<int>> expected{
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };
        // clang-format on

        CAPTURE(matrix);

        set_zeroes(matrix);

        REQUIRE_THAT(matrix, Catch::Matchers::RangeEquals(expected));
    }
}
