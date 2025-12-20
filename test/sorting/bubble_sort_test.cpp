// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/bubble_sort.hpp"

namespace {

using VecIter = std::vector<int>::iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::vector<int>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<VecIter, VecIter>),
    (forfun::sorting::stl::bubble_sort<VecIter, VecIter>)
)
{
    SECTION("Empty container")
    {
        std::vector<int> test_input{};
        std::vector<int> expected_output{};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.empty());

        REQUIRE(test_input == expected_output);
    }

    SECTION("One element")
    {
        std::vector test_input{7};
        std::vector expected_output{7};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 1UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Two elements")
    {
        std::vector test_input{1, 1};
        std::vector expected_output{1, 1};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 2UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Three elements")
    {
        std::vector test_input{-6, 3, 11};
        std::vector expected_output{-6, 3, 11};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 3UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Best case")
    {
        std::vector test_input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Worst case")
    {
        std::vector test_input{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::vector expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 01")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 02")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7UZ);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Negative numbers")
    {
        std::vector test_input{-8, -4, -7, -4, -9, -5, -2};
        std::vector expected_output{-9, -8, -7, -5, -4, -4, -2};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7UZ);

        REQUIRE(test_input == expected_output);
    }
}
