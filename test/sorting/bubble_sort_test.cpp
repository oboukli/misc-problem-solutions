// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/bubble_sort.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 0>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 0>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 0>::iterator>))
{
    SECTION("Empty container")
    {
        std::array<int, 0> test_input{};
        std::array<int, 0> expected_output{};
        bubble_sort(test_input.begin(), test_input.end());

        CHECK(test_input.size() == 0);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 1>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 1>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 1>::iterator>))
{
    SECTION("One element")
    {
        std::array test_input{7};
        std::array expected_output{7};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 1);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 2>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 2>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 2>::iterator>))
{
    SECTION("Two elements")
    {
        std::array test_input{1, 1};
        std::array expected_output{1, 1};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 2);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 3>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 3>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 3>::iterator>))
{
    SECTION("Three elements")
    {
        std::array test_input{-6, 3, 11};
        std::array expected_output{-6, 3, 11};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 3);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 10>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 10>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 10>::iterator>))
{
    SECTION("Best case")
    {
        std::array test_input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Worst case")
    {
        std::array test_input{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        std::array expected_output{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 10);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::array<int, 7>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::array<int, 7>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::array<int, 7>::iterator>))
{
    SECTION("Arbitrary test with std::array")
    {
        std::array test_input{200, 4, 7, 0, 9, -10, 2};
        std::array expected_output{-10, 0, 2, 4, 7, 9, 200};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Bubble sort (std::vector<int>)",
    "[sorting][bubble_sort]",
    ((auto bubble_sort), bubble_sort),
    (forfun::sorting::plain::bubble_sort<std::vector<int>::iterator>),
    (forfun::sorting::stl::bubble_sort<std::vector<int>::iterator>))
{
    SECTION("Arbitrary test with std::vector 01")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), std::prev(test_input.end()));

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Arbitrary test with std::vector 02")
    {
        std::vector test_input{8, 4, 7, 0, 9, 5, 2};
        std::vector expected_output{0, 2, 4, 5, 7, 8, 9};
        bubble_sort(test_input.begin(), test_input.end() - 1);

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }

    SECTION("Negative numbers")
    {
        std::vector test_input{-8, -4, -7, -4, -9, -5, -2};
        std::vector expected_output{-9, -8, -7, -5, -4, -4, -2};
        bubble_sort(test_input.begin(), test_input.end() - 1);

        CHECK(test_input.size() == 7);

        REQUIRE(test_input == expected_output);
    }
}
