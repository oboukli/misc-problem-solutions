// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/sorting/quicksort.hpp"

namespace {

auto fuzz_quicksort(std::vector<int> input) -> void
{
    forfun::sorting::quicksort(input.begin(), input.end());

    ASSERT_TRUE(std::ranges::is_sorted(input));
}

} // namespace

FUZZ_TEST(sorting_quicksort, fuzz_quicksort);
