// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/squares_sorted_array.hpp"

using IntVecConstIter = std::vector<int>::const_iterator;
using IntVecIter = std::vector<int>::iterator;

using UIntVecConstIter = std::vector<unsigned int>::const_iterator;
using UIntVecIter = std::vector<unsigned int>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Squares of a sorted array",
    "[squares_sorted_array]",
    (auto squares_sorted, squares_sorted),
    (forfun::squares_sorted_array::squares_sorted<IntVecConstIter, IntVecIter>),
    // clang-format off
    (forfun::squares_sorted_array::
        squares_sorted_special<IntVecConstIter, IntVecIter>)
    // clang-format on
)
{
    SECTION("Empty input")
    {
        static constexpr std::array<int, 0> expected{};

        std::vector<int> const input{};
        std::vector<int> result_squares{};

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("One element. Element is positive")
    {
        static constexpr std::array const expected{225};

        std::vector const input{15};
        std::vector<int> result_squares(1U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("One element. Element is negative")
    {
        static constexpr std::array const expected{36};

        std::vector const input{-6};
        std::vector<int> result_squares(1U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two elements equal in absolute value")
    {
        static constexpr std::array const expected{25, 25};

        std::vector const input{-5, 5};
        std::vector<int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two non-equal positive elements")
    {
        static constexpr std::array const expected{4, 16};

        std::vector const input{2, 4};
        std::vector<int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two non-equal negative elements")
    {
        static constexpr std::array const expected{4, 49};

        std::vector const input{-7, -2};
        std::vector<int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two elements, one negative and one positive")
    {
        static constexpr std::array const expected{1, 4};

        std::vector const input{-2, 1};
        std::vector<int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three non-equal positive elements")
    {
        static constexpr std::array const expected{1, 9, 49};

        std::vector const input{1, 3, 7};
        std::vector<int> result_squares(3U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three non-equal negative elements")
    {
        static constexpr std::array const expected{9, 16, 25};

        std::vector const input{-5, -4, -3};
        std::vector<int> result_squares(3U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three elements, the first of which is negative (case 1)")
    {
        static constexpr std::array const expected{36, 64, 121};

        std::vector const input{-6, 8, 11};
        std::vector<int> result_squares(3U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three elements, the first of which is negative (case 2)")
    {
        static constexpr std::array expected{9, 16, 100};

        std::vector const input{-4, 3, 10};
        std::vector<int> result_squares(3U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Four elements")
    {
        static constexpr std::array expected{4, 64, 64, 289};

        std::vector const input{-8, 2, 8, 17};
        std::vector<int> result_squares(4U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Five elements")
    {
        static constexpr std::array expected{0, 16, 25, 49, 81};

        std::vector const input{-7, -5, 0, 4, 9};
        std::vector<int> result_squares(5U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    // AI-assisted
    SECTION("Elements from -127 to 128 (benchmark case)")
    {
        static constexpr std::array expected{
            0,     1,     1,     4,     4,     9,     9,     16,    16,
            25,    25,    36,    36,    49,    49,    64,    64,    81,
            81,    100,   100,   121,   121,   144,   144,   169,   169,
            196,   196,   225,   225,   256,   256,   289,   289,   324,
            324,   361,   361,   400,   400,   441,   441,   484,   484,
            529,   529,   576,   576,   625,   625,   676,   676,   729,
            729,   784,   784,   841,   841,   900,   900,   961,   961,
            1024,  1024,  1089,  1089,  1156,  1156,  1225,  1225,  1296,
            1296,  1369,  1369,  1444,  1444,  1521,  1521,  1600,  1600,
            1681,  1681,  1764,  1764,  1849,  1849,  1936,  1936,  2025,
            2025,  2116,  2116,  2209,  2209,  2304,  2304,  2401,  2401,
            2500,  2500,  2601,  2601,  2704,  2704,  2809,  2809,  2916,
            2916,  3025,  3025,  3136,  3136,  3249,  3249,  3364,  3364,
            3481,  3481,  3600,  3600,  3721,  3721,  3844,  3844,  3969,
            3969,  4096,  4096,  4225,  4225,  4356,  4356,  4489,  4489,
            4624,  4624,  4761,  4761,  4900,  4900,  5041,  5041,  5184,
            5184,  5329,  5329,  5476,  5476,  5625,  5625,  5776,  5776,
            5929,  5929,  6084,  6084,  6241,  6241,  6400,  6400,  6561,
            6561,  6724,  6724,  6889,  6889,  7056,  7056,  7225,  7225,
            7396,  7396,  7569,  7569,  7744,  7744,  7921,  7921,  8100,
            8100,  8281,  8281,  8464,  8464,  8649,  8649,  8836,  8836,
            9025,  9025,  9216,  9216,  9409,  9409,  9604,  9604,  9801,
            9801,  10000, 10000, 10201, 10201, 10404, 10404, 10609, 10609,
            10816, 10816, 11025, 11025, 11236, 11236, 11449, 11449, 11664,
            11664, 11881, 11881, 12100, 12100, 12321, 12321, 12544, 12544,
            12769, 12769, 12996, 12996, 13225, 13225, 13456, 13456, 13689,
            13689, 13924, 13924, 14161, 14161, 14400, 14400, 14641, 14641,
            14884, 14884, 15129, 15129, 15376, 15376, 15625, 15625, 15876,
            15876, 16129, 16129, 16384
        };
        static_assert(expected.size() == 256U);

        std::vector const input{
            -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117,
            -116, -115, -114, -113, -112, -111, -110, -109, -108, -107, -106,
            -105, -104, -103, -102, -101, -100, -99,  -98,  -97,  -96,  -95,
            -94,  -93,  -92,  -91,  -90,  -89,  -88,  -87,  -86,  -85,  -84,
            -83,  -82,  -81,  -80,  -79,  -78,  -77,  -76,  -75,  -74,  -73,
            -72,  -71,  -70,  -69,  -68,  -67,  -66,  -65,  -64,  -63,  -62,
            -61,  -60,  -59,  -58,  -57,  -56,  -55,  -54,  -53,  -52,  -51,
            -50,  -49,  -48,  -47,  -46,  -45,  -44,  -43,  -42,  -41,  -40,
            -39,  -38,  -37,  -36,  -35,  -34,  -33,  -32,  -31,  -30,  -29,
            -28,  -27,  -26,  -25,  -24,  -23,  -22,  -21,  -20,  -19,  -18,
            -17,  -16,  -15,  -14,  -13,  -12,  -11,  -10,  -9,   -8,   -7,
            -6,   -5,   -4,   -3,   -2,   -1,   0,    1,    2,    3,    4,
            5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,
            16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
            27,   28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
            38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
            49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
            60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
            71,   72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
            82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,
            93,   94,   95,   96,   97,   98,   99,   100,  101,  102,  103,
            104,  105,  106,  107,  108,  109,  110,  111,  112,  113,  114,
            115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,
            126,  127,  128
        };
        CHECK(input.size() == 256U);

        std::vector<int> result_squares(256U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }
}

TEST_CASE("Squares of a sorted array (unsigned)", "[squares_sorted_array]")
{
    using forfun::squares_sorted_array::squares_sorted;

    SECTION("Empty input")
    {
        static constexpr std::array<unsigned int, 0> expected{};

        std::vector<unsigned int> const input{};
        std::vector<unsigned int> result_squares{};

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("One element. Element is positive")
    {
        static constexpr std::array const expected{225U};

        std::vector const input{15U};
        std::vector<unsigned int> result_squares(1U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two elements equal in absolute value")
    {
        static constexpr std::array const expected{25U, 25U};

        std::vector const input{5U, 5U};
        std::vector<unsigned int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two non-equal positive elements")
    {
        static constexpr std::array const expected{4U, 16U};

        std::vector const input{2U, 4U};
        std::vector<unsigned int> result_squares(2U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Three non-equal positive elements (array of unsigned int case)")
    {
        static constexpr std::array const expected{1U, 9U, 49U};

        std::vector const input{1U, 3U, 7U};
        std::vector<unsigned int> result_squares(3U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Four elements")
    {
        static constexpr std::array expected{1U, 4U, 64U, 289U};

        std::vector const input{1U, 2U, 8U, 17U};
        std::vector<unsigned int> result_squares(4U);

        CAPTURE(input);

        CHECK(std::ranges::is_sorted(input));

        squares_sorted(input.cbegin(), input.cend(), result_squares.begin());

        REQUIRE_THAT(result_squares, Catch::Matchers::RangeEquals(expected));
    }
}
