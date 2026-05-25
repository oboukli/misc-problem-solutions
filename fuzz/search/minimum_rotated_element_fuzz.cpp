// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/search/minimum_rotated_element.hpp"

namespace {

using ElementType = int;
using VectorType = std::vector<ElementType>;
using RotationType = VectorType::difference_type;

[[nodiscard]] auto SortedUniqueVectorAndIndex()
    -> ::fuzztest::Domain<std::pair<VectorType, RotationType>>
{
    return ::fuzztest::FlatMap(
        [](VectorType elements)
            -> ::fuzztest::Domain<std::pair<VectorType, RotationType>> {
            std::ranges::sort(elements);
            return ::fuzztest::PairOf(
                ::fuzztest::Just(elements),
                ::fuzztest::InRange(
                    RotationType{1}, static_cast<RotationType>(elements.size())
                )
            );
        },
        ::fuzztest::NonEmpty(
            // clang-format off
            ::fuzztest::UniqueElementsVectorOf(
                ::fuzztest::Arbitrary<ElementType>()
            )
            .WithMaxSize(64)
            // clang-format on
        )
    );
}

[[nodiscard]] auto RotatedSortedUniqueVector() -> ::fuzztest::Domain<VectorType>
{
    return ::fuzztest::FlatMap(
        [](std::pair<VectorType, RotationType> p)
            -> ::fuzztest::Domain<VectorType> {
            std::ranges::rotate(p.first, std::next(p.first.begin(), p.second));
            return ::fuzztest::Just(p.first);
        },
        SortedUniqueVectorAndIndex()
    );
}

auto fuzz_iterative_find_min(VectorType const& input) -> void
{
    auto const actual{
        forfun::search::minimum_rotated_element::iterative::find_min(
            input.cbegin(), input.cend()
        )
    };

    ASSERT_EQ(actual, std::ranges::min_element(input));
}

auto fuzz_recursive_find_min(VectorType const& input) -> void
{
    auto const actual{
        forfun::search::minimum_rotated_element::recursive::find_min(
            input.cbegin(), input.cend()
        )
    };

    ASSERT_EQ(actual, std::ranges::min_element(input));
}

} // namespace

FUZZ_TEST(minimum_rotated_element, fuzz_iterative_find_min)
    .WithDomains(RotatedSortedUniqueVector());

FUZZ_TEST(minimum_rotated_element, fuzz_recursive_find_min)
    .WithDomains(RotatedSortedUniqueVector());
