// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::adjacent_find_based::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::unordered_set_based::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>)
)
{
    SECTION("One integer")
    {
        std::vector nums{3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two identical integers")
    {
        std::vector nums{3, 3};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two unique items #1")
    {
        std::vector nums{2, 3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two unique items #2")
    {
        std::vector nums{3, 2};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three identical integers")
    {
        std::vector nums{19, 19, 19};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three integers, one of which is unique")
    {
        std::vector nums{19, 7, 19};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three unique integers #1")
    {
        std::vector nums{2, -5, 3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three unique integers #2")
    {
        std::vector nums{3, 2, 1};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Four identical integers")
    {
        std::vector nums{11, 11, 11, 11};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two hundred fifty-six unique primes (benchmark case)")
    {
        std::vector nums{
            293,  1321, 1171, 229,  787,  181,  1361, 1259, 1511, 1367, 929,
            103,  761,  269,  1277, 109,  191,  271,  347,  1409, 1163, 881,
            1523, 631,  1489, 97,   937,  131,  1373, 139,  431,  701,  1543,
            313,  1109, 709,  601,  251,  7,    383,  163,  433,  953,  11,
            719,  599,  3,    641,  1187, 151,  311,  449,  587,  1283, 419,
            1151, 811,  523,  647,  1229, 827,  1427, 1597, 1087, 373,  727,
            1201, 487,  1297, 1129, 1069, 199,  179,  1289, 521,  571,  127,
            911,  1213, 1493, 1103, 1033, 1301, 67,   461,  349,  677,  1051,
            1429, 967,  1193, 41,   1549, 613,  443,  829,  337,  467,  71,
            1291, 101,  1231, 1181, 617,  317,  941,  37,   859,  421,  211,
            439,  1117, 769,  1567, 1097, 1481, 59,   971,  157,  643,  499,
            1031, 29,   1619, 89,   577,  1013, 31,   367,  919,  83,   263,
            1433, 947,  463,  683,  241,  17,   491,  61,   23,   1423, 1279,
            1453, 1399, 1153, 997,  607,  569,  43,   5,    397,  1559, 47,
            751,  173,  883,  733,  983,  877,  823,  757,  809,  509,  1123,
            991,  1571, 773,  1303, 1471, 659,  53,   557,  1019, 13,   887,
            79,   257,  619,  73,   1061, 113,  1327, 1607, 1237, 907,  743,
            1223, 503,  821,  563,  359,  1439, 853,  661,  457,  107,  1091,
            797,  863,  401,  1249, 409,  1217, 1307, 1319, 1009, 283,  233,
            239,  1447, 1583, 691,  739,  977,  1459, 653,  1039, 149,  331,
            389,  1483, 1531, 277,  479,  281,  1063, 19,   839,  167,  1579,
            1609, 307,  857,  673,  1499, 193,  547,  353,  379,  1451, 1613,
            1049, 1553, 1093, 1601, 137,  1487, 197,  593,  2,    541,  1021,
            227,  223,  1381
        };

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::adjacent_find_based::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::unordered_set_based::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>)
)
{
    SECTION("Four sorted unique floats")
    {
        std::vector nums{0.0F, 0.00000001F, 2.0F, 2.001F};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Four unsorted unique floats")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Five unsorted floats, two of which are identical")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F, 2.001F};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }
}

TEST_CASE(
    "Contains duplicate (empty input degenerate case)", "[contains_duplicate]"
)
{
    using forfun::contains_duplicate::adjacent_find_based::contains_duplicate;

    std::vector<int> nums{};

    CAPTURE(nums);

    REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
}
