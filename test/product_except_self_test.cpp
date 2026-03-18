// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstdint>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/product_except_self.hpp"

using IntVecIter = std::vector<int>::iterator;
using IntVecConstIter = std::vector<int>::const_iterator;
using FloatVecConstIter = std::vector<float>::const_iterator;
using FloatVecIter = std::vector<float>::iterator;
using IntArr3ConstIter = std::array<int, 3>::const_iterator;
using IntArr3Iter = std::array<int, 3>::iterator;
using U64ArrConstIter = std::array<std::uint64_t, 16>::const_iterator;
using U64ArrIter = std::array<std::uint64_t, 16>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::vector<int>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        IntVecConstIter,
        IntVecConstIter,
        IntVecIter,
        IntVecIter>),
    (forfun::product_except_self::alg2::product_except_self<
        IntVecConstIter,
        IntVecConstIter,
        IntVecIter,
        IntVecIter>)
)
{
    SECTION("Empty input")
    {
        std::vector<int> const nums{};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual{};

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of one integer")
    {
        std::vector const nums{3};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual{};

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of two integers")
    {
        std::vector const nums{3, 3};
        std::vector<int> const expected{};

        CAPTURE(nums);

        std::vector<int> actual{};

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of three integers")
    {
        std::vector const nums{0, 1, 1};
        std::vector const expected{1, 0, 0};

        CAPTURE(nums);

        std::vector<int> actual(3UZ);

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input is of four integers")
    {
        std::vector const nums{1, 2, 3, 4};
        std::vector const expected{24, 12, 8, 6};

        CAPTURE(nums);

        std::vector<int> actual(4UZ);

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::vector<int>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        FloatVecConstIter,
        FloatVecConstIter,
        FloatVecIter,
        FloatVecIter>),
    (forfun::product_except_self::alg2::product_except_self<
        FloatVecConstIter,
        FloatVecConstIter,
        FloatVecIter,
        FloatVecIter>)
)
{
    SECTION("Input is of four floats, output type is of four floats")
    {
        std::vector const nums{1.0F, 2.0F, 3.0F, 4.0F};
        std::vector const expected{24.0F, 12.0F, 8.0F, 6.0F};

        CAPTURE(nums);

        std::vector<float> actual(4UZ);

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::array<int, 3>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        IntArr3ConstIter,
        IntArr3ConstIter,
        IntArr3Iter,
        IntArr3Iter>),
    (forfun::product_except_self::alg2::product_except_self<
        IntArr3ConstIter,
        IntArr3ConstIter,
        IntArr3Iter,
        IntArr3Iter>)
)
{
    SECTION("Input is of three integers")
    {
        static constexpr std::array const nums{0, 1, 1};
        static constexpr std::array const expected{1, 0, 0};

        CAPTURE(nums);

        std::array<int, 3> actual{};

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (benchmark case)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        U64ArrConstIter,
        U64ArrConstIter,
        U64ArrIter,
        U64ArrIter>),
    (forfun::product_except_self::alg2::product_except_self<
        U64ArrConstIter,
        U64ArrConstIter,
        U64ArrIter,
        U64ArrIter>)
)
{
    SECTION("Factorial product value")
    {
        static constexpr std::array const nums{
            std::uint64_t{1},
            std::uint64_t{2},
            std::uint64_t{3},
            std::uint64_t{4},
            std::uint64_t{5},
            std::uint64_t{6},
            std::uint64_t{7},
            std::uint64_t{8},
            std::uint64_t{9},
            std::uint64_t{10},
            std::uint64_t{11},
            std::uint64_t{12},
            std::uint64_t{13},
            std::uint64_t{14},
            std::uint64_t{15},
            std::uint64_t{0},
        };

        static_assert(nums.size() == 16UZ);

        static constexpr std::array<std::uint64_t, 16> const expected{
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            1'307'674'368'000U
        };

        CAPTURE(nums);

        std::array<std::uint64_t, 16> actual{};

        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}
