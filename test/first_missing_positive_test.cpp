// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/first_missing_positive.hpp"

TEST_CASE("first_missing_positive") {
    using forfun::first_missing_positive::lowest_missing;

    SECTION("Empty container") {
        std::array<int, 0> test_input{};

        CAPTURE(test_input);
        CHECK(test_input.size() == 0);

        REQUIRE(lowest_missing(test_input) == 1);
    }

    SECTION("One number") {
        auto [test_input, expected_output]
            = GENERATE(table<std::array<int, 1>, int>({
                {{-2}, 1},
                {{-1}, 1},
                {{0}, 1},
                {{1}, 2},
                {{2}, 1},
                {{11}, 1},
            }));

        CAPTURE(test_input);
        CHECK(test_input.size() == 1);

        REQUIRE(lowest_missing(test_input) == expected_output);
    }

    SECTION("Two numbers") {
        auto [test_input, expected_output]
            = GENERATE(table<std::vector<int>, int>({
                {{-2, -2}, 1},
                {{-1, -2}, 1},
                {{0, -2}, 1},
                {{0, 0}, 1},
                {{-1, 0}, 1},
                {{0, 1}, 2},
                {{1, 0}, 2},
                {{1, 2}, 3},
                {{2, 1}, 3},
                {{2, 2}, 1},
            }));

        CAPTURE(test_input);
        CHECK(test_input.size() == 2);

        REQUIRE(lowest_missing(test_input) == expected_output);
    }

    SECTION("Three numbers") {
        auto [test_input, expected_output]
            = GENERATE(table<std::vector<int>, int>({
                {{-1, -1, -1}, 1},
                {{-1, 0, 0}, 1},
                {{0, 0, 0}, 1},
                {{0, 0, -1}, 1},
                {{0, 1, 2}, 3},
                {{2, 1, 0}, 3},
                {{11, 2, 1}, 3},
                {{5, 8, 17}, 1},
                {{1, 1, 1}, 2},
                {{3, 3, 3}, 1},
                {{-8, -1, -3}, 1},
            }));

        CAPTURE(test_input);
        CHECK(test_input.size() == 3);

        REQUIRE(lowest_missing(test_input) == expected_output);
    }

    SECTION("Ten numbers") {
        auto [test_input, expected_output]
            = GENERATE(table<std::vector<int>, int>({
                {{-1, -1, -1, -1, -1, -1, -1, -1, -1, 10}, 1},
                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 1},
                {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 2},
                {{6, 6, 6, 6, 1, 6, 6, 2, 3, 4}, 5},
                {{1, 2, 3, 4, 5, 6, 7, 8, 9, 9}, 10},
                {{9, 8, 7, 6, 5, 4, 3, 3, 2, 1}, 10},
                {{1, 2, 3, 4, 5, 5, 4, 3, 2, 1}, 6},
                {{9, 7, 5, 4, 3, 2, 1, 1, 1, 0}, 6},
                {{8, 20, 10, 6, 4, 3, 2, 1, -1, 0}, 5},
                {{7, 11, 6, 6, -1, 4, 1, 2, 7, 2}, 3},
            }));

        CAPTURE(test_input);
        CHECK(test_input.size() == 10);

        REQUIRE(lowest_missing(test_input) == expected_output);
    }
}
