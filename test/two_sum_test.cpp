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
    (forfun::two_sum::map_based::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::quadratic::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::single_pass::two_sum<ConstIter, ConstIter>)
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

    SECTION("Ten integers")
    {
        std::vector const nums{-5, 0, 0, 0, -2, 4, 7, 0, 9, 8};
        static constexpr int const target{-1};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 5)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("First sixty-four prime numbers (benchmark case)")
    {
        std::vector const nums{
            // clang-format off
            131, 89,  61,  37,  103,  5,    41,  73,
            233, 127, 101, 163, 283,  109,  257, 263,
            191, 79,  11,  97,  1601, 7,    211, 43,
            281, 179, 2,   271, 223,  181,  13,  137,
            3,   53,  157, 277, 193,  1607, 71,  269,
            139, 151, 167, 83,  47,   199,  59,  239,
            229, 293, 173, 241, 251,  19,   227, 67,
            17,  197, 29,  113, 149,  31,   107, 23,
            // clang-format on
        };
        static constexpr int const target{1601 + 1607};
        std::array const expected{
            std::next(nums.cbegin(), 20), std::next(nums.cbegin(), 37)
        };

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Two sum II (presorted container)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::map_based::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::presorted::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::quadratic::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::single_pass::two_sum<ConstIter, ConstIter>)
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
