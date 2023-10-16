// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/first_missing_positive.hpp"

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive with vector<int>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<std::vector<int>>),
    (forfun::first_missing_positive::span::lowest_missing<std::vector<int>>))
{
    SECTION("Empty vector")
    {
        std::vector<int> test_input{};

        CAPTURE(test_input);

        CHECK(test_input.size() == 0);

        REQUIRE(sut(test_input) == 1);
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

        REQUIRE(sut(test_input) == expected_output);
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

        REQUIRE(sut(test_input) == expected_output);
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

        REQUIRE(sut(test_input) == expected_output);
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

        REQUIRE(sut(test_input) == expected_output);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 0>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<std::array<int, 0>>),
    (forfun::first_missing_positive::span::lowest_missing<std::array<int, 0>>))
{
    SECTION("Empty array")
    {
        std::array<int, 0> test_input{};

        CAPTURE(test_input);

        STATIC_CHECK(test_input.size() == 0);

        STATIC_REQUIRE(sut(test_input) == 1);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 16>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<std::array<int, 16>>),
    (forfun::first_missing_positive::span::lowest_missing<std::array<int, 16>>))
{
    SECTION("Empty container")
    {
        std::array test_input{9, 9, 7, 5, 4, 3, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0};

        CAPTURE(test_input);

        CHECK(test_input.size() == 16);

        REQUIRE(sut(test_input) == 6);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<char, 2>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<std::array<char, 2>>),
    (forfun::first_missing_positive::span::lowest_missing<std::array<char, 2>>))
{
    SECTION("char")
    {
        std::array<char, 2> test_input{char{1}, char{2}};
        REQUIRE(sut(test_input) == char{3});
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<unsigned int, 3>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<
        std::array<unsigned int, 3>>),
    (forfun::first_missing_positive::span::lowest_missing<
        std::array<unsigned int, 3>>))
{
    SECTION("unsigned int")
    {
        std::array<unsigned int, 3> test_input{1u, 2u, 4u};
        REQUIRE(sut(test_input) == 3u);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<int, 3>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<std::array<int, 3>>),
    (forfun::first_missing_positive::span::lowest_missing<std::array<int, 3>>))
{
    SECTION("int")
    {
        std::array<int, 3> test_input{1, 2, 4};
        REQUIRE(sut(test_input) == 3);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "first_missing_positive array<unsigned long long, 2>",
    "[first_missing_positive]",
    ((auto sut), sut),
    (forfun::first_missing_positive::cast::lowest_missing<
        std::array<unsigned long long, 2>>),
    (forfun::first_missing_positive::span::lowest_missing<
        std::array<unsigned long long, 2>>))
{
    SECTION("unsigned long long")
    {
        std::array<unsigned long long, 2> test_input{2ull, 1ull};
        REQUIRE(sut(test_input) == 3ull);
    }
}
