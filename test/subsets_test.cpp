// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/subsets.hpp"

TEST_CASE("Subsets", "[subsets]")
{
    using forfun::subsets::recursive::explode_subsets;

    SECTION("One element container")
    {
        std::vector const elements{17};

        std::vector<std::vector<int>> const expected{{}, {17}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements.cbegin(), elements.cend())};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(2UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 2UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
    }

    SECTION("One element container with in-place allocator")
    {
        using ElementAllocatorFactory
            = forfun::subsets::ElementInPlaceAllocatorFactory<int, 1>;
        using SubsetAllocatorFactory
            = forfun::subsets::SubsetInPlaceAllocatorFactory<
                int,
                ElementAllocatorFactory::allocator_type,
                1>;

        ElementAllocatorFactory const element_allocator_factory{};
        SubsetAllocatorFactory const subset_allocator_factory{};

        std::vector const elements{17};

        std::vector<
            std::vector<int, ElementAllocatorFactory::allocator_type>,
            SubsetAllocatorFactory::allocator_type> const expected{{}, {17}};

        CAPTURE(elements);

        auto const actual{explode_subsets(
            elements.cbegin(),
            elements.cend(),
            subset_allocator_factory.allocator(),
            element_allocator_factory.allocator()
        )};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(2UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 2UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
    }

    SECTION("Two element container")
    {
        std::vector const elements{5, 7};

        std::vector<std::vector<int>> const expected{{{}, {5}, {7}, {5, 7}}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements.cbegin(), elements.cend())};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(4UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 4UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
        REQUIRE(actual.at(2).capacity() == actual.at(2).size());
        REQUIRE(actual.at(3).capacity() == actual.at(3).size());
    }

    SECTION("Three element container")
    {
        std::vector const elements{1, 2, 3};

        std::vector<std::vector<int>> const expected{
            {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}
        };

        CAPTURE(elements);

        auto const actual{explode_subsets(elements.cbegin(), elements.cend())};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(8UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 8UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
        REQUIRE(actual.at(2).capacity() == actual.at(2).size());
        REQUIRE(actual.at(3).capacity() == actual.at(3).size());
        REQUIRE(actual.at(4).capacity() == actual.at(4).size());
        REQUIRE(actual.at(5).capacity() == actual.at(5).size());
        REQUIRE(actual.at(6).capacity() == actual.at(6).size());
        REQUIRE(actual.at(7).capacity() == actual.at(7).size());
    }

    SECTION("Four element container (benchmark case 1)")
    {
        std::vector const elements{23, 29, 31, 37};

        std::vector<std::vector<int>> const expected{
            {},
            {23},
            {29},
            {31},
            {37},
            {23, 29},
            {23, 31},
            {23, 37},
            {29, 31},
            {29, 37},
            {31, 37},
            {23, 29, 31},
            {23, 31, 37},
            {23, 29, 37},
            {29, 31, 37},
            {23, 29, 31, 37}
        };

        CAPTURE(elements);

        auto const actual{explode_subsets(elements.cbegin(), elements.cend())};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(16UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 16UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
        REQUIRE(actual.at(2).capacity() == actual.at(2).size());
        REQUIRE(actual.at(3).capacity() == actual.at(3).size());
        REQUIRE(actual.at(4).capacity() == actual.at(4).size());
        REQUIRE(actual.at(5).capacity() == actual.at(5).size());
        REQUIRE(actual.at(6).capacity() == actual.at(6).size());
        REQUIRE(actual.at(7).capacity() == actual.at(7).size());

        REQUIRE(actual.at(8).capacity() == actual.at(8).size());
        REQUIRE(actual.at(9).capacity() == actual.at(9).size());
        REQUIRE(actual.at(10).capacity() == actual.at(10).size());
        REQUIRE(actual.at(11).capacity() == actual.at(11).size());
        REQUIRE(actual.at(12).capacity() == actual.at(12).size());
        REQUIRE(actual.at(13).capacity() == actual.at(13).size());
        REQUIRE(actual.at(14).capacity() == actual.at(14).size());
        REQUIRE(actual.at(15).capacity() == actual.at(15).size());
    }

    SECTION("Four element container with in-place allocator (benchmark case 2)")
    {
        using ElementAllocatorFactory
            = forfun::subsets::ElementInPlaceAllocatorFactory<int, 4>;
        using SubsetAllocatorFactory
            = forfun::subsets::SubsetInPlaceAllocatorFactory<
                int,
                ElementAllocatorFactory::allocator_type,
                4>;

        ElementAllocatorFactory const element_allocator_factory{};
        SubsetAllocatorFactory const subset_allocator_factory{};

        std::vector const elements{23, 29, 31, 37};

        std::vector<
            std::vector<int, ElementAllocatorFactory::allocator_type>,
            SubsetAllocatorFactory::allocator_type> const expected{
            {},
            {23},
            {29},
            {31},
            {37},
            {23, 29},
            {23, 31},
            {23, 37},
            {29, 31},
            {29, 37},
            {31, 37},
            {23, 29, 31},
            {23, 31, 37},
            {23, 29, 37},
            {29, 31, 37},
            {23, 29, 31, 37}
        };

        CAPTURE(elements);

        auto const actual{explode_subsets(
            elements.cbegin(),
            elements.cend(),
            subset_allocator_factory.allocator(),
            element_allocator_factory.allocator()
        )};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(16UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 16UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
        REQUIRE(actual.at(1).capacity() == actual.at(1).size());
        REQUIRE(actual.at(2).capacity() == actual.at(2).size());
        REQUIRE(actual.at(3).capacity() == actual.at(3).size());
        REQUIRE(actual.at(4).capacity() == actual.at(4).size());
        REQUIRE(actual.at(5).capacity() == actual.at(5).size());
        REQUIRE(actual.at(6).capacity() == actual.at(6).size());
        REQUIRE(actual.at(7).capacity() == actual.at(7).size());

        REQUIRE(actual.at(8).capacity() == actual.at(8).size());
        REQUIRE(actual.at(9).capacity() == actual.at(9).size());
        REQUIRE(actual.at(10).capacity() == actual.at(10).size());
        REQUIRE(actual.at(11).capacity() == actual.at(11).size());
        REQUIRE(actual.at(12).capacity() == actual.at(12).size());
        REQUIRE(actual.at(13).capacity() == actual.at(13).size());
        REQUIRE(actual.at(14).capacity() == actual.at(14).size());
        REQUIRE(actual.at(15).capacity() == actual.at(15).size());
    }
}

TEST_CASE("Subsets (degenerate case)", "[subsets]")
{
    using forfun::subsets::recursive::explode_subsets;

    SECTION("Empty container")
    {
        std::vector<int> const elements{};

        std::vector<std::vector<int>> const expected{{}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements.cbegin(), elements.cend())};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 1UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
    }

    SECTION("Empty container with in-place allocator")
    {
        using ElementAllocatorFactory
            = forfun::subsets::ElementInPlaceAllocatorFactory<int, 1>;
        using SubsetAllocatorFactory
            = forfun::subsets::SubsetInPlaceAllocatorFactory<
                int,
                ElementAllocatorFactory::allocator_type,
                0>;

        ElementAllocatorFactory const element_allocator_factory{};
        SubsetAllocatorFactory const subset_allocator_factory{};

        std::vector<int> const elements{};

        std::vector<
            std::vector<int, ElementAllocatorFactory::allocator_type>,
            SubsetAllocatorFactory::allocator_type> const expected{{}};

        CAPTURE(elements);

        auto const actual{explode_subsets(
            elements.cbegin(),
            elements.cend(),
            subset_allocator_factory.allocator(),
            element_allocator_factory.allocator()
        )};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1UZ)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );

        REQUIRE(actual.capacity() == 1UZ);

        REQUIRE(actual.front().capacity() == actual.front().size());
    }
}
