// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <utility>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/search/binary_search.hpp"

namespace {

[[nodiscard]] auto AnyHaystackSortedInNonDescendingOrderAndNeedle()
    -> fuzztest::Domain<std::pair<std::vector<int>, int>>
{
    return fuzztest::FlatMap(
        [](std::vector<int> vec)
            -> fuzztest::Domain<std::pair<std::vector<int>, int>> {
            std::ranges::sort(vec);
            return fuzztest::PairOf(
                fuzztest::Just(vec), fuzztest::ElementOf(vec)
            );
        },
        fuzztest::NonEmpty(fuzztest::Arbitrary<std::vector<int>>())
    );
}

void fuzz_iterative(std::pair<std::vector<int>, int> const& haystack_n_needle)
{
    auto result{forfun::search::binary_search::iterative::find(
        haystack_n_needle.first.cbegin(),
        haystack_n_needle.first.cend(),
        haystack_n_needle.second
    )};

    ASSERT_NE(result, haystack_n_needle.first.cend())
        // Workaround FuzzTest not supporting printing
        // std::pair<std::vector<int>, int>
        << "Needle: "
        << haystack_n_needle.second
        << '\n'
        << "Haystack size: "
        << haystack_n_needle.first.size()
        << '\n'
        << "Haystack content: "
        << ::testing::PrintToString(haystack_n_needle.first);

    ASSERT_EQ(*result, haystack_n_needle.second);
}

void fuzz_recursive(std::pair<std::vector<int>, int> const& haystack_n_needle)
{
    auto result{forfun::search::binary_search::recursive::find(
        haystack_n_needle.first.cbegin(),
        haystack_n_needle.first.cend(),
        haystack_n_needle.second
    )};

    ASSERT_NE(result, haystack_n_needle.first.cend())
        // Workaround FuzzTest not supporting printing
        // std::pair<std::vector<int>, int>
        << "Needle: "
        << haystack_n_needle.second
        << '\n'
        << "Haystack size: "
        << haystack_n_needle.first.size()
        << '\n'
        << "Haystack content: "
        << ::testing::PrintToString(haystack_n_needle.first);

    ASSERT_EQ(*result, haystack_n_needle.second);
}

} // namespace

FUZZ_TEST(binary_search, fuzz_iterative)
    .WithDomains(AnyHaystackSortedInNonDescendingOrderAndNeedle());

FUZZ_TEST(binary_search, fuzz_recursive)
    .WithDomains(AnyHaystackSortedInNonDescendingOrderAndNeedle());
