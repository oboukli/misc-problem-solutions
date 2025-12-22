// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>
#include <cstddef>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/binary_search.hpp"

namespace {

template <std::size_t Size>
using StdArrayConstIter = std::array<int, Size>::const_iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Binary search in empty collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstIter<0>, StdArrayConstIter<0>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstIter<0>, StdArrayConstIter<0>, int>)
    // clang-format on
)
{
    static constexpr int const target{151};
    static constexpr std::array<int, 0> const records{};
    static_assert(records.empty());

    STATIC_REQUIRE(
        find(records.cbegin(), records.cend(), target) == records.cend()
    );
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in one-element collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstIter<1>, StdArrayConstIter<1>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstIter<1>, StdArrayConstIter<1>, int>)
    // clang-format on
)
{
    SECTION("One-element collection, containing the target")
    {
        static constexpr int const target{277};
        static constexpr std::array const records{277};
        static_assert(records.size() == 1UZ);

        constexpr auto const result{
            find(records.cbegin(), records.cend(), target)
        };

        STATIC_CHECK(result == records.cbegin());
        STATIC_REQUIRE(*result == 277);
    }

    SECTION("One-element collection, not containing the target")
    {
        static constexpr int const target{19};
        static constexpr std::array const records{7};
        static_assert(records.size() == 1UZ);

        STATIC_CHECK(std::ranges::is_sorted(records));

        constexpr auto const result{
            find(records.cbegin(), records.cend(), target)
        };

        STATIC_REQUIRE(result == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in two-element collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstIter<2>, StdArrayConstIter<2>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstIter<2>, StdArrayConstIter<2>, int>)
    // clang-format on
)
{
    SECTION("Two-element collection, containing the target (case 1)")
    {
        static constexpr int const target{5519};
        static constexpr std::array const records{5519, 5521};

        STATIC_CHECK(std::ranges::is_sorted(records));

        constexpr auto const result{
            find(records.cbegin(), records.cend(), target)
        };

        STATIC_REQUIRE_FALSE(result == records.cend());
        STATIC_REQUIRE(*result == 5519);
    }

    SECTION("Two-element collection, containing the target (case 2)")
    {
        static constexpr int const target{5521};
        static constexpr std::array const records{5519, 5521};

        STATIC_CHECK(std::ranges::is_sorted(records));

        constexpr auto const result{
            find(records.cbegin(), records.cend(), target)
        };

        STATIC_REQUIRE_FALSE(result == records.cend());
        STATIC_REQUIRE(*result == 5521);
    }

    SECTION("Two-element collection, not containing the target")
    {
        static constexpr int const target{19};
        static constexpr std::array const records{5519, 5521};

        STATIC_CHECK(std::ranges::is_sorted(records));

        constexpr auto const result{
            find(records.cbegin(), records.cend(), target)
        };

        STATIC_REQUIRE(result == records.cend());
    }
}
