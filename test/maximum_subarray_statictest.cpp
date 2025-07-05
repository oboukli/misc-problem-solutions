// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/maximum_subarray.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Maximum subarray constexpr tests (empty array case)",
    "[maximum_subarray]",
    (auto max_sum, max_sum),
    (forfun::maximum_subarray::brute_force::max_sum<
        std::array<int, 0>::const_iterator,
        std::array<int, 0>::const_iterator>),
    (forfun::maximum_subarray::recursive::max_sum<
        std::array<int, 0>::const_iterator,
        std::array<int, 0>::const_iterator>),
    (forfun::maximum_subarray::streaming::max_sum<
        std::array<int, 0>::const_iterator,
        std::array<int, 0>::const_iterator>)
)
{
    static constexpr std::array<int, 0> const input{};

    STATIC_REQUIRE(max_sum(input.cbegin(), input.cend()) == 0);
}

TEMPLATE_TEST_CASE_SIG(
    "Maximum subarray constexpr tests (one integer case)",
    "[maximum_subarray]",
    (auto max_sum, max_sum),
    (forfun::maximum_subarray::brute_force::max_sum<
        std::array<int, 1>::const_iterator,
        std::array<int, 1>::const_iterator>),
    (forfun::maximum_subarray::recursive::max_sum<
        std::array<int, 1>::const_iterator,
        std::array<int, 1>::const_iterator>),
    (forfun::maximum_subarray::streaming::max_sum<
        std::array<int, 1>::const_iterator,
        std::array<int, 1>::const_iterator>)
)
{
    static constexpr std::array const input{17};
    static_assert(input.size() == 1UZ);

    STATIC_REQUIRE(max_sum(input.cbegin(), input.cend()) == 17);
}

TEMPLATE_TEST_CASE_SIG(
    "Maximum subarray constexpr tests (two integers case)",
    "[maximum_subarray]",
    (auto max_sum, max_sum),
    (forfun::maximum_subarray::brute_force::max_sum<
        std::array<int, 2>::const_iterator,
        std::array<int, 2>::const_iterator>),
    (forfun::maximum_subarray::recursive::max_sum<
        std::array<int, 2>::const_iterator,
        std::array<int, 2>::const_iterator>),
    (forfun::maximum_subarray::streaming::max_sum<
        std::array<int, 2>::const_iterator,
        std::array<int, 2>::const_iterator>)
)
{
    static constexpr std::array const input{61, 67};

    STATIC_REQUIRE(max_sum(input.cbegin(), input.cend()) == 128);
}
