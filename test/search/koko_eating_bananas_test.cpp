// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/koko_eating_bananas.hpp"

TEST_CASE("Koko eating bananas", "[koko_eating_bananas]")
{
    using forfun::search::koko_eating_bananas::min_eating_speed;

    SECTION("One pile")
    {
        static constexpr int const duration{1};
        std::vector const piles{191};
        CHECK(piles.size() == 1UZ);

        static constexpr int const expected{191};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Two piles")
    {
        static constexpr int const duration{3};
        std::vector const piles{83, 89};

        static constexpr int const expected{83};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Number of piles is equal to duration")
    {
        static constexpr int const duration{4};
        std::vector const piles{11, 5, 19, 1};

        static constexpr int const expected{19};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Five equal piles")
    {
        static constexpr int const duration{7};
        std::vector const piles{3, 3, 3, 3, 3};

        static constexpr int const expected{3};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Five inequal piles (case 1)")
    {
        static constexpr int const duration{7};
        std::vector const piles{1, 2, 3, 4, 5};

        static constexpr int const expected{3};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Five inequal piles (case 2)")
    {
        static constexpr int const duration{100};
        std::vector const piles{1, 2, 3, 4, 5};

        static constexpr int const expected{1};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("Sixteen inequal piles (benchmark case)")
    {
        static constexpr int const duration{17};
        std::vector const piles{
            311,
            383,
            359,
            367,
            313,
            307,
            317,
            337,
            347,
            353,
            331,
            379,
            349,
            283,
            373,
            293,
        };

        static constexpr int const expected{379};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("LeetCode case 1")
    {
        static constexpr int const duration{8};
        std::vector const piles{3, 6, 7, 11};

        static constexpr int const expected{4};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("LeetCode case 2")
    {
        static constexpr int const duration{5};
        std::vector const piles{30, 11, 23, 4, 20};

        static constexpr int const expected{30};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("LeetCode case 3")
    {
        static constexpr int const duration{6};
        std::vector const piles{30, 11, 23, 4, 20};

        static constexpr int const expected{23};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("NeetCode case 1")
    {
        static constexpr int const duration{9};
        std::vector const piles{1, 4, 3, 2};

        static constexpr int const expected{2};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }

    SECTION("NeetCode case 2")
    {
        static constexpr int const duration{4};
        std::vector const piles{25, 10, 23, 4};

        static constexpr int const expected{25};

        CAPTURE(duration);
        CAPTURE(piles);

        REQUIRE(
            min_eating_speed(piles.cbegin(), piles.cend(), duration) == expected
        );
    }
}
