// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/insertion_sort.hpp"

TEST_CASE("Insertion sort", "[sorting][insertion_sort]")
{
    using forfun::sorting::insertion_sort;

    SECTION("Empty container")
    {
        std::array<int, 0U> test_input{};
        static constexpr std::array<int, 0U> const expected_output{};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.empty());

        REQUIRE(test_input == expected_output);
    }

    SECTION("One element")
    {
        std::array test_input{7};
        static constexpr std::array const expected_output{7};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 1U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Two elements")
    {
        std::array test_input{1, 1};
        static constexpr std::array const expected_output{1, 1};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 2U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Three elements")
    {
        std::array test_input{-6, 3, 11};
        static constexpr std::array const expected_output{-6, 3, 11};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 3U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Best case")
    {
        std::array test_input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        static constexpr std::array const expected_output{
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Worst case")
    {
        std::array test_input{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        static constexpr std::array const expected_output{
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test (case 1)")
    {
        std::array test_input{200, 4, 7, 0, 9, -10, 2};
        static constexpr std::array const expected_output{
            -10, 0, 2, 4, 7, 9, 200
        };
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test (case 2)")
    {
        std::array test_input{8, 4, 7, 0, 9, 5, 2};
        std::array const expected_output{0, 2, 4, 5, 7, 8, 9};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test (case 3)")
    {
        std::array test_input{8, 4, 7, 0, 9, 5, 2};
        std::array const expected_output{0, 2, 4, 5, 7, 8, 9};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7U);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Negative numbers")
    {
        std::array test_input{-8, -4, -7, -4, -9, -5, -2};
        std::array const expected_output{-9, -8, -7, -5, -4, -4, -2};
        insertion_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7U);

        REQUIRE(test_input == expected_output);
    }
}
