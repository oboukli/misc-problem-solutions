// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/insertion.hpp"

TEST_CASE("Insertion sort") {
    using forfun::sorting::insertion_sort;

    SECTION("Empty container") {
        std::array<int, 0> test_input{};
        std::array<int, 0> expected_output{};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 0);

        REQUIRE(test_input == expected_output);
    }

    SECTION("One element") {
        std::array test_input{7};
        std::array expected_output{7};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 1);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Two elements") {
        std::array test_input{1, 1};
        std::array expected_output{1, 1};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 2);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Three elements") {
        std::array test_input{-6, 3, 11};
        std::array expected_output{-6, 3, 11};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 3);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Best case") {
        std::array test_input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Worst case") {
        std::array test_input{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::array") {
        std::array test_input{200, 4, 7, 0, 9, -10, 2};
        std::array expected_output{-10, 0, 2, 4, 7, 9, 200};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 01") {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 02") {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Negative numbers") {
        std::vector test_input{-8, -4, -7, -4, -9, -5, -2};
        std::vector expected_output{-9, -8, -7, -5, -4, -4, -2};
        insertion_sort(test_input, test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }
}
