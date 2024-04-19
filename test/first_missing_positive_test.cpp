// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/first_missing_positive.hpp"

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive with vector<int>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::vector<int>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::vector<int>::iterator>))
{
    SECTION("Empty vector")
    {
        std::vector<int> test_input{};

        CAPTURE(test_input);

        CHECK(test_input.empty());

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end()) == 1);
    }

    SECTION("One number")
    {
        auto [test_input, expected_output]{
            GENERATE(table<std::vector<int>, int>({
                {{-2}, 1},
                {{-1}, 1},
                {{0}, 1},
                {{1}, 2},
                {{2}, 1},
                {{11}, 1},
            }))};

        CAPTURE(test_input);

        CHECK(test_input.size() == 1);

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end())
            == expected_output);
    }

    SECTION("Two numbers")
    {
        auto [test_input, expected_output]{
            GENERATE(table<std::vector<int>, int>({
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
            }))};

        CAPTURE(test_input);

        CHECK(test_input.size() == 2);

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end())
            == expected_output);
    }

    SECTION("Three numbers")
    {
        auto [test_input, expected_output]{
            GENERATE(table<std::vector<int>, int>({
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
            }))};

        CAPTURE(test_input);

        CHECK(test_input.size() == 3);

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end())
            == expected_output);
    }

    SECTION("Ten numbers")
    {
        auto [test_input, expected_output]{
            GENERATE(table<std::vector<int>, int>({
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
            }))};

        CAPTURE(test_input);

        CHECK(test_input.size() == 10);

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end())
            == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 0>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<int, 0>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<int, 0>::iterator>))
{
    SECTION("Empty array")
    {
        std::array<int, 0> test_input{};

        CAPTURE(test_input);

        STATIC_CHECK(test_input.empty());

        STATIC_REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end()) == 1);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 16>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<int, 16>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<int, 16>::iterator>))
{
    SECTION("Empty container")
    {
        std::array test_input{9, 9, 7, 5, 4, 3, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0};

        CAPTURE(test_input);

        CHECK(test_input.size() == 16);

        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end()) == 6);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<char, 2>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<char, 2>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<char, 2>::iterator>))
{
    SECTION("char")
    {
        std::array<char, 2> test_input{char{1}, char{2}};
        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end())
            == char{3});
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<unsigned int, 3>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<unsigned int, 3>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<unsigned int, 3>::iterator>))
{
    SECTION("unsigned int")
    {
        std::array<unsigned int, 3> test_input{1U, 2U, 4U};
        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end()) == 3U);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 3>",
    "[first_missing_positive]",
    ((auto first_missing_positive), first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<int, 3>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<int, 3>::iterator>))
{
    SECTION("int")
    {
        std::array<int, 3> test_input{1, 2, 4};
        REQUIRE(
            first_missing_positive(test_input.begin(), test_input.end()) == 3);
    }
}
