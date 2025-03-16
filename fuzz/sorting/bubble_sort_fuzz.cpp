// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/sorting/bubble_sort.hpp"

namespace {

auto fuzz_plain_bubble_sort(std::vector<int> input) -> void
{
    forfun::sorting::plain::bubble_sort(input.begin(), input.end());

    ASSERT_TRUE(std::ranges::is_sorted(input));
}

auto fuzz_stl_bubble_sort(std::vector<int> input) -> void
{
    forfun::sorting::stl::bubble_sort(input.begin(), input.end());

    ASSERT_TRUE(std::ranges::is_sorted(input));
}

} // namespace

FUZZ_TEST(sorting_bubble_sort, fuzz_plain_bubble_sort);

FUZZ_TEST(sorting_bubble_sort, fuzz_stl_bubble_sort);
