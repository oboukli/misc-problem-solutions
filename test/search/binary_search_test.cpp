// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>
#include <iterator>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/binary_search.hpp"

namespace {

template <std::size_t Size>
using StdArrayConstItr = std::array<int, Size>::const_iterator;

using StdVectorConstItr = std::vector<int>::const_iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Binary search in empty collection",
    "[search][binary_search]",
    ((auto find), find),
    (forfun::search::binary_search::recursive::find<StdArrayConstItr<0>, int>))
{
    constexpr int const target{151};
    std::array<int, 0> const records{};
    static_assert(records.empty());

    REQUIRE(find(records.cbegin(), records.cend(), target) == records.cend());
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in one-element collection",
    "[search][binary_search]",
    ((auto find), find),
    (forfun::search::binary_search::recursive::find<StdArrayConstItr<1>, int>))
{
    SECTION("One-element collection, containing the target")
    {
        constexpr int const target{277};
        std::array const records{277};
        static_assert(records.size() == 1);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK(result == records.cbegin());
        REQUIRE(*result == 277);
    }

    SECTION("One-element collection, not containing the target")
    {
        constexpr int const target{19};
        std::array const records{7};
        static_assert(records.size() == 1);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE(result == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in even collection",
    "[search][binary_search]",
    ((auto find), find),
    (forfun::search::binary_search::recursive::find<StdArrayConstItr<12>, int>))
{
    SECTION("Even collection containing the target once")
    {
        constexpr int const target{5};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 2));
        REQUIRE(*result == 5);
    }

    SECTION("Even collection containing the target even times")
    {
        constexpr int const target{163};
        std::array const records{
            149, 151, 157, 163, 163, 163, 163, 181, 191, 193, 197, 199};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 163);
    }

    SECTION("Even collection containing the target odd times")
    {
        constexpr int const target{257};
        std::array const records{
            227, 229, 233, 239, 241, 251, 257, 257, 257, 271, 277, 281};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 257);
    }

    SECTION("Even collection containing the target at the lower offset")
    {
        constexpr int const target{2};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == records.cbegin());
        REQUIRE(*result == 2);
    }

    SECTION("Even collection containing the target at the upper offset")
    {
        constexpr int const target{37};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == (++records.crbegin()).base());
        REQUIRE(*result == 37);
    }

    SECTION("Even collection not containing the in-range target")
    {
        constexpr int const target{35};
        constexpr std::array const records{
            29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
        static_assert(records.size() == 12);
        static_assert(target > records.front());
        static_assert(target < records.back());

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }

    SECTION("Even collection where target is smaller than smallest element")
    {
        constexpr int const target{1};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }

    SECTION("Even collection where target is larger than largest element")
    {
        constexpr int const target{41};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        static_assert(records.size() == 12);

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in odd collection",
    "[search][binary_search]",
    ((auto find), find),
    (forfun::search::binary_search::recursive::find<StdArrayConstItr<11>, int>))
{
    SECTION("Odd collection containing the target once")
    {
        constexpr int const target{23};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 8));
        REQUIRE(*result == 23);
    }

    SECTION("Odd collection containing the target even times")
    {
        constexpr int const target{17};
        std::array const records{2, 3, 5, 7, 11, 17, 17, 17, 17, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 5));
        REQUIRE(*result == 17);
    }

    SECTION("Odd collection containing the target odd times")
    {
        constexpr int const target{239};
        std::array const records{
            227, 229, 233, 239, 239, 239, 257, 263, 269, 271, 277};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 5));
        REQUIRE(*result == 239);
    }

    SECTION("Odd collection containing the target at the lower offset")
    {
        constexpr int const target{2};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == records.cbegin());
        REQUIRE(*result == 2);
    }

    SECTION("Odd collection containing the target at the upper offset")
    {
        constexpr int const target{31};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == (++records.crbegin()).base());
        REQUIRE(*result == 31);
    }

    SECTION("Odd collection not containing the in-range target")
    {
        constexpr int const target{35};
        constexpr std::array const records{
            29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
        static_assert(records.size() == 11);
        static_assert(target > records.front());
        static_assert(target < records.back());

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }

    SECTION("Odd collection where target is smaller than smallest element")
    {
        constexpr int const target{1};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }

    SECTION("Odd collection where target is larger than largest element")
    {
        constexpr int const target{41};
        std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        static_assert(records.size() == 11);

        CAPTURE(records);
        CAPTURE(target);

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search with std::vector",
    "[search][binary_search]",
    ((auto find), find),
    (forfun::search::binary_search::recursive::find<StdVectorConstItr, int>))
{
    SECTION("Even collection (vector) containing the target odd times")
    {
        constexpr int const target{257};
        std::vector const records{
            227, 229, 233, 239, 241, 251, 257, 257, 257, 271, 277, 281};

        CAPTURE(records);
        CAPTURE(target);

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 257);
    }
}
