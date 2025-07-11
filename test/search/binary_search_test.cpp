// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
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
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<0>, StdArrayConstItr<0>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<0>, StdArrayConstItr<0>, int>)
    // clang-format on
)
{
    static constexpr int const target{151};
    static constexpr std::array<int, 0> const records{};
    static_assert(records.empty());

    REQUIRE(find(records.cbegin(), records.cend(), target) == records.cend());
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in one-element collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<1>, StdArrayConstItr<1>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<1>, StdArrayConstItr<1>, int>)
    // clang-format on
)
{
    SECTION("One-element collection, containing the target")
    {
        static constexpr int const target{277};
        static constexpr std::array const records{277};
        static_assert(records.size() == 1UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK(result == records.cbegin());
        REQUIRE(*result == 277);
    }

    SECTION("One-element collection, not containing the target")
    {
        static constexpr int const target{19};
        static constexpr std::array const records{7};
        static_assert(records.size() == 1UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE(result == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in two-element collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<2>, StdArrayConstItr<2>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<2>, StdArrayConstItr<2>, int>)
    // clang-format on
)
{
    SECTION("Two-element collection, containing the target (case 1)")
    {
        static constexpr int const target{5519};
        static constexpr std::array const records{5519, 5521};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK_FALSE(result == records.cend());
        REQUIRE(*result == 5519);
    }

    SECTION("Two-element collection, containing the target (case 2)")
    {
        static constexpr int const target{5521};
        static constexpr std::array const records{5519, 5521};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK_FALSE(result == records.cend());
        REQUIRE(*result == 5521);
    }

    SECTION("Two-element collection, not containing the target")
    {
        static constexpr int const target{19};
        static constexpr std::array const records{5519, 5521};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE(result == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in three-element collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<3>, StdArrayConstItr<3>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<3>, StdArrayConstItr<3>, int>)
    // clang-format on
)
{
    SECTION("Three-element collection, containing the target (case 1)")
    {
        static constexpr int const target{-1};
        static constexpr std::array const records{-1, 1, 2};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK_FALSE(result == records.cend());
        REQUIRE(*result == -1);
    }

    SECTION("Three-element collection, containing the target (case 2)")
    {
        static constexpr int const target{1};
        static constexpr std::array const records{-1, 1, 2};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK_FALSE(result == records.cend());
        REQUIRE(*result == 1);
    }

    SECTION("Three-element collection, containing the target (case 3)")
    {
        static constexpr int const target{2};
        static constexpr std::array const records{-1, 1, 2};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        CHECK_FALSE(result == records.cend());
        REQUIRE(*result == 2);
    }

    SECTION("Three-element collection, not containing the target")
    {
        static constexpr int const target{19};
        static constexpr std::array const records{-1, 1, 2};

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE(result == records.cend());
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in even collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<12>, StdArrayConstItr<12>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<12>, StdArrayConstItr<12>, int>)
    // clang-format on
)
{
    SECTION("Even collection containing the target once")
    {
        static constexpr int const target{5};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 2));
        REQUIRE(*result == 5);
    }

    SECTION("Even collection containing the target even times")
    {
        static constexpr int const target{163};
        static constexpr std::array const records{
            149, 151, 157, 163, 163, 163, 163, 181, 191, 193, 197, 199
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 163);
    }

    SECTION("Even collection containing the target odd times")
    {
        static constexpr int const target{257};
        static constexpr std::array const records{
            227, 229, 233, 239, 241, 251, 257, 257, 257, 271, 277, 281
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 257);
    }

    SECTION("Even collection containing the target at the lower offset")
    {
        static constexpr int const target{2};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == records.cbegin());
        REQUIRE(*result == 2);
    }

    SECTION("Even collection containing the target at the upper offset")
    {
        static constexpr int const target{37};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == (++records.crbegin()).base());
        REQUIRE(*result == 37);
    }

    SECTION("Even collection not containing the in-range target")
    {
        static constexpr int const target{35};
        static constexpr std::array const records{
            29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73
        };
        static_assert(records.size() == 12UZ);
        static_assert(target > records.front());
        static_assert(target < records.back());

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }

    SECTION("Even collection where target is smaller than smallest element")
    {
        static constexpr int const target{1};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }

    SECTION("Even collection where target is larger than largest element")
    {
        static constexpr int const target{41};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
        };
        static_assert(records.size() == 12UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search in odd collection",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::iterative::
        find<StdArrayConstItr<11>, StdArrayConstItr<11>, int>),
    (forfun::search::binary_search::recursive::
        find<StdArrayConstItr<11>, StdArrayConstItr<11>, int>)
    // clang-format on
)
{
    SECTION("Odd collection containing the target once")
    {
        static constexpr int const target{23};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 8));
        REQUIRE(*result == 23);
    }

    SECTION("Odd collection containing the target even times")
    {
        static constexpr int const target{17};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 17, 17, 17, 17, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 5));
        REQUIRE(*result == 17);
    }

    SECTION("Odd collection containing the target odd times")
    {
        static constexpr int const target{239};
        static constexpr std::array const records{
            227, 229, 233, 239, 239, 239, 257, 263, 269, 271, 277
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 5));
        REQUIRE(*result == 239);
    }

    SECTION("Odd collection containing the target at the lower offset")
    {
        static constexpr int const target{2};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == records.cbegin());
        REQUIRE(*result == 2);
    }

    SECTION("Odd collection containing the target at the upper offset")
    {
        static constexpr int const target{31};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == (++records.crbegin()).base());
        REQUIRE(*result == 31);
    }

    SECTION("Odd collection not containing the in-range target")
    {
        static constexpr int const target{35};
        static constexpr std::array const records{
            29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71
        };
        static_assert(records.size() == 11UZ);
        static_assert(target > records.front());
        static_assert(target < records.back());

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }

    SECTION("Odd collection where target is smaller than smallest element")
    {
        static constexpr int const target{1};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }

    SECTION("Odd collection where target is larger than largest element")
    {
        static constexpr int const target{41};
        static constexpr std::array const records{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };
        static_assert(records.size() == 11UZ);

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        REQUIRE(
            find(records.cbegin(), records.cend(), target) == records.cend()
        );
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Binary search with std::vector",
    "[search][binary_search]",
    (auto find, find),
    // clang-format off
    (forfun::search::binary_search::recursive::
        find<StdVectorConstItr, StdVectorConstItr, int>)
    // clang-format on
)
{
    SECTION("Even collection (vector) containing the target odd times")
    {
        static constexpr int const target{257};
        std::vector const records{
            227, 229, 233, 239, 241, 251, 257, 257, 257, 271, 277, 281
        };

        CAPTURE(records);
        CAPTURE(target);

        CHECK(std::ranges::is_sorted(records));

        auto const result{find(records.cbegin(), records.cend(), target)};

        REQUIRE_FALSE(result == records.cend());
        CHECK(result == std::next(records.cbegin(), 6));
        REQUIRE(*result == 257);
    }
}
