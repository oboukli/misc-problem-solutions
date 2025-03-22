// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/squares_sorted_array.hpp"

namespace {

auto fuzz_squares_sorted(std::vector<int> const& input) -> void
{
    std::vector<int> result_squares(input.size());

    forfun::squares_sorted_array::squares_sorted(
        input.cbegin(), input.cend(), result_squares.begin()
    );

    ASSERT_TRUE(std::ranges::is_sorted(result_squares));
}

auto fuzz_squares_sorted_special(std::vector<int> const& input) -> void
{
    std::vector<int> result_squares(input.size());

    forfun::squares_sorted_array::squares_sorted_special(
        input.cbegin(), input.cend(), result_squares.begin()
    );

    ASSERT_TRUE(std::ranges::is_sorted(result_squares));
}

auto SortedVectorOfArbitraryInts() -> ::fuzztest::Domain<std::vector<int>>
{
    /*static constexpr*/ int const max_safe{
        static_cast<int>(std::floor(std::sqrt(std::numeric_limits<int>::max())))
    };
    /*static constexpr*/ int const min_safe{-1 * max_safe};

    return ::fuzztest::Map(
        [](std::vector<int>&& vec) -> std::vector<int> {
            std::vector<int> vec_(std::move(vec));
            std::ranges::sort(vec_);

            return vec_;
        },
        ::fuzztest::VectorOf(::fuzztest::InRange(min_safe, max_safe))
    );
}

} // namespace

FUZZ_TEST(squares_sorted_array, fuzz_squares_sorted)
    .WithDomains(SortedVectorOfArbitraryInts());

FUZZ_TEST(squares_sorted_array, fuzz_squares_sorted_special)
    .WithDomains(SortedVectorOfArbitraryInts());
