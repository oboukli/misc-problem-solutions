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
    "Two sum",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::brute_force::two_sum<ConstIter, ConstIter>),
    (forfun::two_sum::map_based::two_sum<ConstIter, ConstIter>)
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

    SECTION("Input length is one")
    {
        std::vector const nums{3};
        static constexpr int const target{3};
        std::array const expected{nums.cend(), nums.cend()};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input length is two")
    {
        std::vector const nums{3, 3};
        static constexpr int const target{6};
        std::array const expected{nums.cbegin(), std::next(nums.cbegin(), 1)};

        CAPTURE(nums);
        CAPTURE(target);

        auto const actual{two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Input has negative integers")
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

    SECTION("Sorted input 1")
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

    SECTION("Sorted input 2")
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

    SECTION("Unsorted input with repeated elements")
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

    SECTION("Unsorted input 1")
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

    SECTION("Unsorted input 2")
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

    SECTION("Unsorted input 3")
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

    SECTION("Unsorted input 4")
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

    SECTION("Unsorted input 5 (benchmark case)")
    {
        std::vector const nums{
            2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
            43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101,
            103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
            173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
            241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
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
}

TEST_CASE("Two sum static tests", "[two_sum]")
{
    using forfun::two_sum::brute_force::two_sum;

    SECTION("Empty input")
    {
        static constexpr std::array<int, 0U> const nums{};
        static constexpr int const target{0};
        static constexpr std::array const expected{nums.cend(), nums.cend()};

        CAPTURE(nums);
        CAPTURE(target);

        static constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)
        };

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Unsorted input")
    {
        static constexpr std::array const nums{3, 2, 4};
        static constexpr int const target{6};
        static constexpr std::array const expected{
            std::next(nums.cbegin(), 1), std::next(nums.cbegin(), 2)
        };

        CAPTURE(nums);
        CAPTURE(target);

        static constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)
        };

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}
