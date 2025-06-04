// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <limits>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/hamming_weight.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Humming weight",
    "[hamming_weight]",
    (auto get_hamming_weight, get_hamming_weight),
    forfun::hamming_weight::linear_functional::get_hamming_weight,
    forfun::hamming_weight::linear_imperative::get_hamming_weight,
    forfun::hamming_weight::optimized_imperative::get_hamming_weight
)
{
    SECTION("Zero")
    {
        STATIC_REQUIRE(get_hamming_weight(0) == 0UZ);
    }

    SECTION("Max std::size_t value")
    {
        STATIC_REQUIRE(
            get_hamming_weight(std::numeric_limits<std::size_t>::max())
            == std::numeric_limits<std::size_t>::digits
        );
    }
}
