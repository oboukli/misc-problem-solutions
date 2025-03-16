// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/sorting/insertion_sort.hpp"

namespace {

auto fuzz_insertion_sort(std::vector<int> input) -> void
{
    forfun::sorting::insertion_sort(input.begin(), input.end());

    ASSERT_TRUE(std::ranges::is_sorted(input));
}

} // namespace

FUZZ_TEST(sorting_insertion_sort, fuzz_insertion_sort);
