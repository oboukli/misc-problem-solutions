// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "forfun/subsets.hpp"

#ifdef _MSC_VER
TEST_CASE("Subsets", "[subsets]")
{
    WARN(
        "Skipped Subsets static test on MSVC due to a potential compiler "
        "and/or standard library issue."
    );
}
#else
TEST_CASE("Subsets", "[subsets]")
{
    using forfun::subsets::explode_subsets;

    SECTION("One element container")
    {
        STATIC_REQUIRE(explode_subsets(std::vector{17}).size() == 2UZ);
    }

    SECTION("Two element container")
    {
        STATIC_REQUIRE(explode_subsets(std::vector{5, 7}).size() == 4UZ);
    }
}

TEST_CASE("Subsets (degenerate case)", "[subsets]")
{
    using forfun::subsets::explode_subsets;

    SECTION("Empty container")
    {
        STATIC_REQUIRE(explode_subsets(std::vector<int>{}).size() == 1UZ);
    }
}
#endif // _MSC_VER
