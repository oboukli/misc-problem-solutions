// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sub_array_sums.hpp"

TEST_CASE("sub_array_sums", "[sub_array_sums]")
{
    using forfun::sub_array_sums::sum_each;

    SECTION("Zero window size of empty array, take all")
    {
        std::vector<int> const numbers{};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{0};
        std::vector const expected{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("Zero window size of empty array none")
    {
        std::vector<int> const numbers{};
        std::vector<int> sums{};
        constexpr std::vector<int>::size_type const sub_size{0};
        std::vector<int> const expected{};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("None of one")
    {
        std::vector const numbers{5};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{0};
        std::vector const expected{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("None of two")
    {
        std::vector const numbers{{7, 11}};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{0};
        std::vector const expected{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of one")
    {
        std::vector const numbers{13};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{1};
        std::vector const expected{13};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("All of two")
    {
        std::vector const numbers{{2, 3}};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{2};
        std::vector const expected{5};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("All of three")
    {
        std::vector const numbers{{3, 11, 17}};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{3};
        std::vector const expected{31};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of two")
    {
        std::vector const numbers{{19, 23}};
        std::vector<int> sums(2);
        constexpr std::vector<int>::size_type const sub_size{1};
        std::vector const expected{{19, 23}};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of three")
    {
        std::vector const numbers{{29, 31, 37}};
        std::vector<int> sums(3);
        constexpr std::vector<int>::size_type const sub_size{1};
        std::vector const expected{{29, 31, 37}};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION(
        "Given non-empty array, "
        "when sub size is larger than size, "
        "then sum all")
    {
        std::vector const numbers{{1, 2, 3}};
        std::vector<int> sums(1);
        constexpr std::vector<int>::size_type const sub_size{101};
        std::vector const expected{6};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("2 of 6")
    {
        std::vector const numbers{{1, 2, 2, 1, 1, 2}};
        std::vector<int> sums(5);
        constexpr std::vector<int>::size_type const sub_size{2};
        std::vector const expected{{3, 4, 3, 2, 3}};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(4);
        constexpr std::vector<int>::size_type const sub_size{3};
        std::vector const expected{{3, 4, 5, 6}};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take 2")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(2);
        constexpr std::vector<int>::size_type const sub_size{3};
        std::vector const expected{{3, 4}};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take 3")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(3);
        constexpr std::vector<int>::size_type const sub_size{3};
        std::vector const expected{{3, 4, 5}};

        CAPTURE(numbers);
        CAPTURE(sub_size);
        CAPTURE(sums.size());
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take all (std::array)")
    {
        static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
        std::array<int, 4> sums{3, 4, 5, 6};
        static constexpr std::array<int, 6>::size_type const sub_size{3};
        static constexpr std::array const expected{3, 4, 5, 6};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take all, do not mutate excess (std::array)")
    {
        static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
        std::array<int, 6> sums{-1, -1, -1, -1, -1, -1};
        static constexpr std::array<int, 6>::size_type const sub_size{3};
        static constexpr std::array const expected{3, 4, 5, 6, -1, -1};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }
}
