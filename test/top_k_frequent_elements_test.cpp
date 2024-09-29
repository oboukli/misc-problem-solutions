// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/top_k_frequent_elements.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Top K frequent elements",
    "[top_k_frequent_elements]",
    (auto top_frequent, top_frequent),
    // clang-format off
    (forfun::top_k_frequent_elements::priority_queue_based::top_frequent<
        std::vector<int>::const_iterator,
        std::vector<int>::const_iterator>),
    (forfun::top_k_frequent_elements::unordered_map_based::top_frequent<
        std::vector<int>::const_iterator,
        std::vector<int>::const_iterator>)
    // clang-format on
)
{
    SECTION("Top zero of empty")
    {
        std::vector<int> nums{};
        static constexpr int const k{0U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top two of empty")
    {
        std::vector<int> nums{};
        static constexpr int const k{2U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top three of empty")
    {
        std::vector<int> nums{};
        static constexpr int const k{3U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top zero of one element")
    {
        std::vector nums{5};
        static constexpr int const k{0U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top zero of two elements")
    {
        std::vector nums{11, 13};
        static constexpr int const k{0U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top zero of three elements")
    {
        std::vector nums{11, 13, 17};
        static constexpr int const k{0U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::IsEmpty());
    }

    SECTION("Top one of one element")
    {
        std::vector nums{7};
        static constexpr int const k{1U};

        static constexpr std::array const expected{7};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top one of two elements")
    {
        std::vector nums{11, 13};
        static constexpr int const k{1U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::SizeIs(1U));
    }

    SECTION("Top one of three elements")
    {
        std::vector nums{11, 13, 17};
        static constexpr int const k{1U};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::SizeIs(1U));
    }

    SECTION("Top four of two elements")
    {
        std::vector nums{11, 13};
        static constexpr int const k{4U};

        static constexpr std::array const expected{11, 13};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(2U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top four of three elements")
    {
        std::vector nums{11, 13, 17};
        static constexpr int const k{4U};

        static constexpr std::array const expected{11, 13, 17};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(3U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top five of two elements")
    {
        std::vector nums{11, 13};
        static constexpr int const k{5U};

        static constexpr std::array const expected{11, 13};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(2U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top five of three elements")
    {
        std::vector nums{11, 13, 17};
        static constexpr int const k{5U};

        static constexpr std::array const expected{11, 13, 17};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(3U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top one of three identical elements")
    {
        std::vector nums{19, 19, 19};
        static constexpr int const k{1U};

        static constexpr std::array const expected{19};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top one of four identical elements")
    {
        std::vector nums{19, 19, 19, 19};
        static constexpr int const k{1U};

        static constexpr std::array const expected{19};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Top three of six elements")
    {
        std::vector nums{23, 43, 31, 43, 23, 43};
        static constexpr int const k{3U};

        static constexpr std::array const expected{43, 31, 23};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Top three of three unique elements")
    {
        std::vector nums{23, 31, 43};
        static constexpr int const k{3U};

        static constexpr std::array const expected{23, 31, 43};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Top four of four unique elements")
    {
        std::vector nums{19, 23, 31, 43};
        static constexpr int const k{4U};

        static constexpr std::array const expected{19, 23, 31, 43};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Signed integers")
    {
        std::vector nums{5, -9, -8, -9, 42, 42, -8, -8, 42, 42};
        static constexpr int const k{2U};

        static constexpr std::array const expected{42, -8};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Top two of seventeen elements (benchmark case)")
    {
        std::vector nums{5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2};
        static constexpr int const k{2U};

        static constexpr std::array const expected{7, 11};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("LeetCode test case 1")
    {
        std::vector nums{1, 1, 1, 2, 2, 3};
        static constexpr int const k{2U};

        static constexpr std::array const expected{1, 2};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("LeetCode test case 2")
    {
        std::vector nums{1};
        static constexpr int const k{1U};

        static constexpr std::array const expected{1};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("NeetCode test case 1")
    {
        std::vector nums{1, 2, 2, 3, 3, 3};
        static constexpr int const k{2U};

        static constexpr std::array const expected{2, 3};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("NeetCode test case 2")
    {
        std::vector nums{7, 7};
        static constexpr int const k{1U};

        static constexpr std::array const expected{7};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("GeeksforGeeks test case 1")
    {
        std::vector nums{3, 1, 4, 4, 5, 2, 6, 1};
        static constexpr int const k{2U};

        static constexpr std::array const expected{1, 4};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("GeeksforGeeks test case 2")
    {
        std::vector nums{7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9};
        static constexpr int const k{3U};

        static constexpr std::array const expected{5, 7, 11};

        CAPTURE(nums);
        CAPTURE(k);

        std::vector const actual{top_frequent(nums.begin(), nums.end(), k)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}
