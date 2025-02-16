// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <iterator>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/two_sum.hpp"

using ConstIter = std::vector<int>::const_iterator;

TEMPLATE_TEST_CASE_SIG(
    "Two sum (unsorted container)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::quadratic::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::map_based::two_sum<ConstIter, ConstIter>)
)
{
    SECTION("Two integers")
    {
        std::vector const nums{3, 2};
        static constexpr int const target{5};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 1)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Three integers (case 1)")
    {
        std::vector const nums{3, 2, 4};
        static constexpr int const target{6};
        std::array const expected{
            std::next(nums.cbegin(), 1), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Three integers (case 2)")
    {
        std::vector const nums{3, 2, 4};
        static constexpr int const target{7};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Four integers (case 1)")
    {
        std::vector const nums{1, 4, 10, -3};
        static constexpr int const target{14};
        std::array const expected{
            std::next(nums.cbegin(), 1), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Four integers (case 2)")
    {
        std::vector const nums{9, 5, 1, 23};
        static constexpr int const target{10};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Five integers")
    {
        std::vector const nums{0, -1, 2, -3, 1};
        static constexpr int const target{-2};
        std::array const expected{
            std::next(nums.cbegin(), 3), std::next(nums.cbegin(), 4)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Two sum (presorted container)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::quadratic::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::map_based::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::presorted::two_sum<ConstIter, ConstIter>)
)
{
    SECTION("Empty input")
    {
        std::vector<int> const nums{};
        static constexpr int const target{0};
        std::array const expected{nums.cend(), nums.cend()};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("One integer")
    {
        std::vector const nums{3};
        static constexpr int const target{3};
        std::array const expected{nums.cend(), nums.cend()};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Two integers")
    {
        std::vector const nums{3, 3};
        static constexpr int const target{6};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 1)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Three integers")
    {
        std::vector const nums{7, 11, 13};
        static constexpr int const target{20};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 2)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Four integers (case 1)")
    {
        std::vector const nums{2, 7, 11, 15};
        static constexpr int const target{22};
        std::array const expected{
            std::next(nums.cbegin(), 1), std::next(nums.cbegin(), 3)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Four integers (case 2)")
    {
        std::vector const nums{-5, -2, 4, 7};
        static constexpr int const target{-1};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 2)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Four identical integers")
    {
        std::vector const nums{19, 19, 19, 19};
        static constexpr int const target{38};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 1)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("First sixty-four prime numbers (benchmark case)")
    {
        std::vector const nums{
            // clang-format off
            2,   3,   5,   7,   11,  13,  17,  19,
            23,  29,  31,  37,  41,  43,  47,  53,
            59,  61,  67,  71,  73,  79,  83,  89,
            97,  101, 103, 107, 109, 113, 127, 131,
            137, 139, 149, 151, 157, 163, 167, 173,
            179, 181, 191, 193, 197, 199, 211, 223,
            227, 229, 233, 239, 241, 251, 257, 263,
            269, 271, 277, 281, 283, 293, 307, 311,
            // clang-format on
        };
        static constexpr int const target{307 + 311};
        std::array const expected{
            std::next(nums.cbegin(), 62), std::next(nums.cbegin(), 63)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("LeetCode Two Sum II case 1")
    {
        std::vector const nums{2, 7, 11, 15};
        static constexpr int const target{9};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 1)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("LeetCode Two Sum II case 2")
    {
        std::vector const nums{2, 3, 4};
        static constexpr int const target{6};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("LeetCode Two Sum II case 3")
    {
        std::vector const nums{-1, 0};
        static constexpr int const target{-1};
        std::array const expected{
            std::next(nums.cbegin(), 0), std::next(nums.cbegin(), 1)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}
