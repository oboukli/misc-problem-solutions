// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/product_except_self.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::vector<int>)",
    "[product_except_self]",
    ((auto product_except_self), product_except_self),
    (forfun::product_except_self::base::product_except_self<
        std::vector<int>::const_iterator,
        std::vector<int>::iterator>),
    (forfun::product_except_self::fast::product_except_self<
        std::vector<int>::const_iterator,
        std::vector<int>::iterator>))
{
    SECTION("Empty input")
    {
        std::vector<int> const nums{};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual;
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of one integer")
    {
        std::vector const nums{3};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual;
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of two integers")
    {
        std::vector const nums{3, 3};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual;
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of three integers")
    {
        std::vector const nums{0, 1, 1};
        std::vector const expected{1, 0, 0};

        CAPTURE(nums);

        std::vector<int> actual(3);
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of four integers")
    {
        std::vector const nums{1, 2, 3, 4};
        std::vector const expected{24, 12, 8, 6};

        CAPTURE(nums);

        std::vector<int> actual(4);
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::vector<int>)",
    "[product_except_self]",
    ((auto product_except_self), product_except_self),
    (forfun::product_except_self::base::product_except_self<
        std::vector<float>::const_iterator,
        std::vector<double>::iterator>),
    (forfun::product_except_self::fast::product_except_self<
        std::vector<float>::const_iterator,
        std::vector<double>::iterator>))
{
    SECTION("Input is of four integers, output type is float")
    {
        std::vector const nums{1.0f, 2.0f, 3.0f, 4.0f};
        std::vector const expected{24.0, 12.0, 8.0, 6.0};

        CAPTURE(nums);

        std::vector<double> actual(4);
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::array<int, 3>)",
    "[product_except_self]",
    ((auto product_except_self), product_except_self),
    (forfun::product_except_self::base::product_except_self<
        std::array<int, 3>::const_iterator,
        std::array<int, 3>::iterator>),
    (forfun::product_except_self::fast::product_except_self<
        std::array<int, 3>::const_iterator,
        std::array<int, 3>::iterator>))
{
    SECTION("Input is of three integers")
    {
        constexpr std::array const nums{0, 1, 1};
        constexpr std::array const expected{1, 0, 0};

        CAPTURE(nums);

        std::array<int, 3> actual;
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end());

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}
