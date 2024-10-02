// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/maximum_subarray.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Maximum subarray",
    "[maximum_subarray]",
    (auto max_sum, max_sum),
    (forfun::maximum_subarray::recursive::max_sum<
        std::vector<int>::const_iterator,
        std::vector<int>::const_iterator>),
    (forfun::maximum_subarray::streaming::max_sum<
        std::vector<int>::const_iterator,
        std::vector<int>::const_iterator>)
)
{
    SECTION("Empty array")
    {
        std::vector<int> const input{};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 0);
    }

    SECTION("One element; element is zero")
    {
        std::vector const input{0};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 0);
    }

    SECTION("One element; element is negative")
    {
        std::vector const input{-1};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == -1);
    }

    SECTION("Two elements, all positive")
    {
        std::vector const input{1, 9};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 10);
    }

    SECTION("Three elements, all positive")
    {
        std::vector const input{5, 1, 9};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 15);
    }

    SECTION("Two elements, all negative")
    {
        std::vector const input{-1, -9};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == -1);
    }

    SECTION("Three elements, all negative")
    {
        std::vector const input{-5, -1, -9};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == -1);
    }

    SECTION("Arbitrary test case 1 (benchmark case)")
    {
        std::vector const input{0, 52, -100, 0, 1, 30, -6, 33};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 58);
    }

    SECTION("Arbitrary test case 2")
    {
        std::vector const input{42, -42, 1, 13};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 42);
    }

    SECTION("Arbitrary test case 3")
    {
        std::vector const input{-3, -2, -1, -5, -1};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == -1);
    }

    SECTION("LeetCode test case 1")
    {
        std::vector const input{-2, 1, -3, 4, -1, 2, 1, -5, 4};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 6);
    }

    SECTION("LeetCode test case 2")
    {
        std::vector const input{1};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 1);
    }

    SECTION("LeetCode test case 3")
    {
        std::vector const input{5, 4, -1, 7, 8};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 23);
    }

    SECTION("GeeksforGeeks test case 1")
    {
        std::vector const input{2, 3, -8, 7, -1, 2, 3};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 11);
    }

    SECTION("GeeksforGeeks test case 2")
    {
        std::vector const input{-2, -4};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == -2);
    }

    SECTION("GeeksforGeeks test case 3")
    {
        std::vector const input{5, 4, 1, 7, 8};

        CAPTURE(input);

        REQUIRE(max_sum(input.cbegin(), input.cend()) == 25);
    }
}
