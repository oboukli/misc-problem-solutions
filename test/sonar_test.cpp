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
        Sonar const sonar{{{.x = 0, .y = 0}}};

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
        Sonar const sonar{{
            // clang-format off
            {.x = 0, .y = 7},
            {.x = 2, .y = 5},
            {.x = 3, .y = 3},
            {.x = 4, .y = 6},
            {.x = 5, .y = 2},
            // clang-format on
        }};

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
        Sonar const sonar{{
            // clang-format off
            {.x = 1, .y = 1},
            {.x = 2, .y = 2},
            {.x = 3, .y = 3},
            {.x = 4, .y = 4},
            {.x = 5, .y = 5},
            // clang-format on
        }};

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
        Sonar const sonar{{{.x = 345, .y = 456}}};

        int const num_ships{count_ships(
            sonar, {.top = 1, .bottom = 1000, .left = 1, .right = 1000})};
        REQUIRE(num_ships == 1);
    }

    SECTION("Test sonar 5")
    {
        Sonar const sonar{{{
            // clang-format off
            {.x = 102, .y = 430}, {.x = 488, .y = 821},
            {.x = 863, .y = 875}, {.x = 820, .y = 684},
            {.x = 453, .y = 603}, {.x = 99,  .y = 476},
            {.x = 516, .y = 730}, {.x = 582, .y = 54},
            {.x = 349, .y = 987}, {.x = 541, .y = 437},
            {.x = 572, .y = 947}, {.x = 189, .y = 21},
            {.x = 6,   .y = 533}, {.x = 99,  .y = 229},
            {.x = 694, .y = 675}, {.x = 816, .y = 1},
            {.x = 669, .y = 555}, {.x = 753, .y = 916},
            {.x = 602, .y = 260}, {.x = 194, .y = 708},
            {.x = 371, .y = 886}, {.x = 461, .y = 562},
            {.x = 106, .y = 781}, {.x = 379, .y = 509},
            {.x = 38,  .y = 255}, {.x = 337, .y = 427},
            {.x = 991, .y = 482}, {.x = 161, .y = 11},
            {.x = 125, .y = 802}, {.x = 818, .y = 813},
            {.x = 377, .y = 644}, {.x = 185, .y = 336},
            {.x = 185, .y = 114}, {.x = 567, .y = 627},
            {.x = 800, .y = 891}, {.x = 734, .y = 55},
            {.x = 4,   .y = 906}, {.x = 490, .y = 175},
            {.x = 622, .y = 509}, {.x = 797, .y = 839},
            {.x = 876, .y = 511}, {.x = 130, .y = 609},
            {.x = 362, .y = 783}, {.x = 333, .y = 865},
            {.x = 563, .y = 913}, {.x = 217, .y = 18},
            {.x = 311, .y = 913}, {.x = 420, .y = 397},
            {.x = 383, .y = 438}, {.x = 289, .y = 741},
            {.x = 338, .y = 231}, {.x = 113, .y = 564},
            {.x = 421, .y = 588}, {.x = 108, .y = 788},
            {.x = 283, .y = 829}, {.x = 37,  .y = 204},
            {.x = 558, .y = 800}, {.x = 64,  .y = 693},
            {.x = 248, .y = 399}, {.x = 142, .y = 217},
            {.x = 160, .y = 603}, {.x = 771, .y = 62},
            {.x = 19,  .y = 905}, {.x = 393, .y = 383},
            {.x = 709, .y = 484}, {.x = 376, .y = 246},
            {.x = 51,  .y = 769}, {.x = 895, .y = 597},
            {.x = 78,  .y = 776}, {.x = 209, .y = 461},
            {.x = 414, .y = 361}, {.x = 213, .y = 57},
            {.x = 199, .y = 721}, {.x = 343, .y = 305},
            {.x = 628, .y = 921}, {.x = 8,   .y = 535},
            {.x = 594, .y = 958}, {.x = 918, .y = 539},
            {.x = 652, .y = 370}, {.x = 258, .y = 811},
            {.x = 780, .y = 977}, {.x = 812, .y = 994},
            {.x = 811, .y = 684}, {.x = 586, .y = 201},
            {.x = 550, .y = 721}, {.x = 62,  .y = 448},
            {.x = 709, .y = 875}, {.x = 127, .y = 106},
            {.x = 965, .y = 881}, {.x = 886, .y = 989},
            {.x = 718, .y = 115}, {.x = 239, .y = 140},
            {.x = 397, .y = 965}, {.x = 464, .y = 598},
            {.x = 684, .y = 609}, {.x = 228, .y = 766},
            {.x = 886, .y = 944}, {.x = 14,  .y = 64},
            {.x = 143, .y = 956},
            // clang-format on
        }}};

        int const num_ships{count_ships(
            sonar, {.top = 1, .bottom = 1000, .left = 1, .right = 1000})};
        REQUIRE(num_ships == 99);
    }
}
