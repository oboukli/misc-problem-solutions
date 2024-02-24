// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/sonar.hpp"

TEST_CASE("sonar", "[sonar]")
{
    using namespace forfun::sonar;

    SECTION("Test sonar 1")
    {
        Sonar const sonar{{{0, 0}}};

        auto const [area, expected_num_ships]{GENERATE(table<Area, int>({
            {{0, 0, 0, 0}, 1},
            {{0, 0, 1, 3}, 0},
            {{0, 5, 0, 7}, 1},
            {{0, 0, 0, 7}, 1},
        }))};

        int const num_ships{count_ships(sonar, area)};
        REQUIRE(num_ships == expected_num_ships);
    }

    SECTION("Test sonar 2")
    {
        Sonar const sonar{{{0, 7}, {2, 5}, {3, 3}, {4, 6}, {5, 2}}};

        auto const [area, expected_num_ships]{GENERATE(table<Area, int>({
            {{0, 0, 7, 7}, 1},
            {{0, 5, 1, 5}, 3},
            {{0, 5, 2, 7}, 5}, // Benchmark case
            {{1, 3, 0, 2}, 0},
        }))};

        int const num_ships{count_ships(sonar, area)};
        REQUIRE(num_ships == expected_num_ships);
    }

    SECTION("Test sonar 3")
    {
        Sonar const sonar{{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}};

        auto const [area, expected_num_ships]{GENERATE(table<Area, int>({
            {{1, 1, 1, 1}, 1},
            {{1, 2, 1, 2}, 2},
            {{1, 5, 1, 5}, 5},
        }))};

        int const num_ships{count_ships(sonar, area)};
        REQUIRE(num_ships == expected_num_ships);
    }

    SECTION("Test sonar 4")
    {
        Sonar const sonar{{{345, 456}}};

        int const num_ships{count_ships(sonar, {1, 1000, 1, 1000})};
        REQUIRE(num_ships == 1);
    }

    SECTION("Test sonar 5")
    {
        Sonar const sonar{{{
            // clang-format off
            {102, 430}, {488, 821}, {863, 875}, {820, 684}, {453, 603},
            {99, 476},  {516, 730}, {582, 54},  {349, 987}, {541, 437},
            {572, 947}, {189, 21},  {6, 533},   {99, 229},  {694, 675},
            {816, 1},   {669, 555}, {753, 916}, {602, 260}, {194, 708},
            {371, 886}, {461, 562}, {106, 781}, {379, 509}, {38, 255},
            {337, 427}, {991, 482}, {161, 11},  {125, 802}, {818, 813},
            {377, 644}, {185, 336}, {185, 114}, {567, 627}, {800, 891},
            {734, 55},  {4, 906},   {490, 175}, {622, 509}, {797, 839},
            {876, 511}, {130, 609}, {362, 783}, {333, 865}, {563, 913},
            {217, 18},  {311, 913}, {420, 397}, {383, 438}, {289, 741},
            {338, 231}, {113, 564}, {421, 588}, {108, 788}, {283, 829},
            {37, 204},  {558, 800}, {64, 693},  {248, 399}, {142, 217},
            {160, 603}, {771, 62},  {19, 905},  {393, 383}, {709, 484},
            {376, 246}, {51, 769},  {895, 597}, {78, 776},  {209, 461},
            {414, 361}, {213, 57},  {199, 721}, {343, 305}, {628, 921},
            {8, 535},   {594, 958}, {918, 539}, {652, 370}, {258, 811},
            {780, 977}, {812, 994}, {811, 684}, {586, 201}, {550, 721},
            {62, 448},  {709, 875}, {127, 106}, {965, 881}, {886, 989},
            {718, 115}, {239, 140}, {397, 965}, {464, 598}, {684, 609},
            {228, 766}, {886, 944}, {14, 64},   {143, 956}
            // clang-format on
        }}};

        int const num_ships{count_ships(sonar, {1, 1000, 1, 1000})};
        REQUIRE(num_ships == 99);
    }
}
