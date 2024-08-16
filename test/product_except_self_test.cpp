// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/product_except_self.hpp"

using IntVecItr = std::vector<int>::iterator;
using IntVecConstItr = std::vector<int>::const_iterator;
using FloatVecConstItr = std::vector<float>::const_iterator;
using DoubleVecItr = std::vector<double>::iterator;
using IntArr3ConstItr = std::array<int, 3U>::const_iterator;
using IntArr3Itr = std::array<int, 3U>::iterator;
using U64ArrConstItr = std::array<std::uint64_t, 16U>::const_iterator;
using U64ArrItr = std::array<std::uint64_t, 16U>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::vector<int>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        IntVecConstItr,
        IntVecConstItr,
        IntVecItr,
        IntVecItr>),
    (forfun::product_except_self::alg2::product_except_self<
        IntVecConstItr,
        IntVecConstItr,
        IntVecItr,
        IntVecItr>)
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

        std::vector<int> actual(3U);
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

        std::vector<int> actual(4U);
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
        FloatVecConstItr,
        FloatVecConstItr,
        DoubleVecItr,
        DoubleVecItr>),
    (forfun::product_except_self::alg2::product_except_self<
        FloatVecConstItr,
        FloatVecConstItr,
        DoubleVecItr,
        DoubleVecItr>)
)
{
    SECTION("Input is of four integers, output type is float")
    {
        std::vector const nums{1.0F, 2.0F, 3.0F, 4.0F};
        std::vector const expected{24.0, 12.0, 8.0, 6.0};

        CAPTURE(nums);

        std::vector<double> actual(4U);
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Product of array except self (std::array<int, 3U>)",
    "[product_except_self]",
    (auto product_except_self, product_except_self),
    (forfun::product_except_self::alg1::product_except_self<
        IntArr3ConstItr,
        IntArr3ConstItr,
        IntArr3Itr,
        IntArr3Itr>),
    (forfun::product_except_self::alg2::product_except_self<
        IntArr3ConstItr,
        IntArr3ConstItr,
        IntArr3Itr,
        IntArr3Itr>)
)
{
    SECTION("Input is of three integers")
    {
        static constexpr std::array const nums{0, 1, 1};
        static constexpr std::array const expected{1, 0, 0};

        CAPTURE(nums);

        std::array<int, 3U> actual{};
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
        U64ArrConstItr,
        U64ArrConstItr,
        U64ArrItr,
        U64ArrItr>),
    (forfun::product_except_self::alg2::product_except_self<
        U64ArrConstItr,
        U64ArrConstItr,
        U64ArrItr,
        U64ArrItr>)
)
{
    SECTION("Factorial product value")
    {
        static constexpr std::array const nums{
            std::uint64_t{1U},
            std::uint64_t{2U},
            std::uint64_t{3U},
            std::uint64_t{4U},
            std::uint64_t{5U},
            std::uint64_t{6U},
            std::uint64_t{7U},
            std::uint64_t{8U},
            std::uint64_t{9U},
            std::uint64_t{10U},
            std::uint64_t{11U},
            std::uint64_t{12U},
            std::uint64_t{13U},
            std::uint64_t{14U},
            std::uint64_t{15U},
            std::uint64_t{0U},
        };

        static_assert(nums.size() == std::size_t{16U});

        static constexpr std::array<std::uint64_t, 16U> const expected{
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

        std::array<std::uint64_t, 16U> actual{};
        product_except_self(
            nums.cbegin(), nums.cend(), actual.begin(), actual.end()
        );

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }
}

TEST_CASE("Product except self (concepts)", "[product_except_self]")
{
    SECTION("Concept product_computable")
    {
        using forfun::product_except_self::concepts::product_computable;

        struct Dummy final {};

        STATIC_REQUIRE(product_computable<short, int>);
        STATIC_REQUIRE(product_computable<int, int>);
        STATIC_REQUIRE(product_computable<std::int32_t, std::int64_t>);
        STATIC_REQUIRE(product_computable<std::int64_t, std::int64_t>);
        STATIC_REQUIRE(product_computable<int, float>);
        STATIC_REQUIRE(product_computable<float, float>);
        STATIC_REQUIRE(product_computable<float, double>);

        STATIC_REQUIRE_FALSE(product_computable<bool, bool>);
        STATIC_REQUIRE_FALSE(product_computable<Dummy, int>);
        STATIC_REQUIRE_FALSE(product_computable<std::int32_t, std::int16_t>);
        STATIC_REQUIRE_FALSE(product_computable<std::int64_t, std::int32_t>);
        STATIC_REQUIRE_FALSE(product_computable<double, float>);
    }
}
