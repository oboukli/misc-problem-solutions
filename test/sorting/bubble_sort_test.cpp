// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/bubble_sort.hpp"

using Arr0Itr = std::array<int, 0>::iterator;
using Arr1Itr = std::array<int, 1>::iterator;
using Arr2Itr = std::array<int, 2>::iterator;
using Arr3Itr = std::array<int, 3>::iterator;
using Arr7Itr = std::array<int, 7>::iterator;
using Arr10Itr = std::array<int, 10>::iterator;
using VecItr = std::vector<int>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 0>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr0Itr, Arr0Itr>),
    (forfun::sorting::stl::bubble_sort<Arr0Itr, Arr0Itr>))
{
    SECTION("Empty container")
    {
        std::array<int, 0> test_input{};
        std::array<int, 0> expected_output{};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.empty());

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 1>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr1Itr, Arr1Itr>),
    (forfun::sorting::stl::bubble_sort<Arr1Itr, Arr1Itr>))
{
    SECTION("One element")
    {
        std::array test_input{7};
        std::array expected_output{7};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 1);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 2>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr2Itr, Arr2Itr>),
    (forfun::sorting::stl::bubble_sort<Arr2Itr, Arr2Itr>))
{
    SECTION("Two elements")
    {
        std::array test_input{1, 1};
        std::array expected_output{1, 1};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 2);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 3>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr3Itr, Arr3Itr>),
    (forfun::sorting::stl::bubble_sort<Arr3Itr, Arr3Itr>))
{
    SECTION("Three elements")
    {
        std::array test_input{-6, 3, 11};
        std::array expected_output{-6, 3, 11};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 3);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 10>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr10Itr, Arr10Itr>),
    (forfun::sorting::stl::bubble_sort<Arr10Itr, Arr10Itr>))
{
    SECTION("Best case")
    {
        std::array test_input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Worst case")
    {
        std::array test_input{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 7>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<Arr7Itr, Arr7Itr>),
    (forfun::sorting::stl::bubble_sort<Arr7Itr, Arr7Itr>))
{
    SECTION("Arbitrary test with std::array")
    {
        std::array test_input{200, 4, 7, 0, 9, -10, 2};
        std::array expected_output{-10, 0, 2, 4, 7, 9, 200};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::vector<int>)",
    "[sorting][bubble_sort]",
    (auto bubble_sort, bubble_sort),
    (forfun::sorting::plain::bubble_sort<VecItr, VecItr>),
    (forfun::sorting::stl::bubble_sort<VecItr, VecItr>))
{
    SECTION("Arbitrary test with std::vector 01")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 02")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Negative numbers")
    {
        std::vector test_input{-8, -4, -7, -4, -9, -5, -2};
        std::vector expected_output{-9, -8, -7, -5, -4, -4, -2};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }
}
