// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "forfun/first_missing_positive.hpp"

TEST_CASE("first_missing_positive") {
    using forfun::first_missing_positive::lowest_missing;

    SECTION("Basic") {
        REQUIRE(lowest_missing({}) == 1);
        REQUIRE(lowest_missing({0}) == 1);
        REQUIRE(lowest_missing({1}) == 2);
        REQUIRE(lowest_missing({2}) == 1);
    }

    SECTION("Two elements") {
        REQUIRE(lowest_missing({-1, 0}) == 1);
        REQUIRE(lowest_missing({0, 1}) == 2);
        REQUIRE(lowest_missing({1, 0}) == 2);
        REQUIRE(lowest_missing({1, 2}) == 3);
        REQUIRE(lowest_missing({2, 1}) == 3);
    }

    SECTION("Duplicates") {
        REQUIRE(lowest_missing({0, 0, 0, 0}) == 1);
        REQUIRE(lowest_missing({1, 1, 1, 1}) == 2);
        REQUIRE(lowest_missing({6, 6, 6, 6, 6}) == 1);
        REQUIRE(lowest_missing({6, 6, 6, 6, 1}) == 2);
    }

    SECTION("Negative numbers") {
        REQUIRE(lowest_missing({-2}) == 1);
        REQUIRE(lowest_missing({-1}) == 1);
        REQUIRE(lowest_missing({-1, -1, -1, -1}) == 1);
        REQUIRE(lowest_missing({-6, -5, -4, 1, 2}) == 3);
    }

    SECTION("Misc") {
        REQUIRE(lowest_missing({1, 2, 3, 4, 5, 6, 7, 8, 9}) == 10);
        REQUIRE(lowest_missing({9, 8, 7, 6, 5, 4, 3, 2, 1}) == 10);
        REQUIRE(lowest_missing({1, 2, 3, 4, 5, 4, 3, 2, 1}) == 6);
        REQUIRE(lowest_missing({9, 7, 5, 4, 3, 2, 1}) == 6);
        REQUIRE(lowest_missing({8, 20, 10, 5, 4, 3, 2, 1}) == 6);
        REQUIRE(lowest_missing({7, 11, 6, 6, -1, 4, 1, 2}) == 3);
    }

    SECTION("Test cases copied from Simon Toth)") {
        REQUIRE(lowest_missing({9, 8, 7, 4, 3, 2, 1}) == 5);
        REQUIRE(lowest_missing({1, 1}) == 2);
    }

    SECTION("Test cases copied from LeetCode") {
        REQUIRE(lowest_missing({1, 2, 0}) == 3);
        REQUIRE(lowest_missing({3, 4, -1, 1}) == 2);
        REQUIRE(lowest_missing({7, 8, 9, 11, 12}) == 1);
    }
}
