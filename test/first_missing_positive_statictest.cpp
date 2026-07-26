// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/first_missing_positive.hpp"

TEMPLATE_TEST_CASE_SIG(
    "First missing positive (array<int, 16>)",
    "[first_missing_positive]",
    (auto first_missing_positive, first_missing_positive),
    (forfun::first_missing_positive::base::lowest_missing<
        std::array<int, 16>::iterator,
        std::array<int, 16>::iterator>),
    (forfun::first_missing_positive::fast::lowest_missing<
        std::array<int, 16>::iterator,
        std::array<int, 16>::iterator>)
)
{
    static constexpr auto result{[] [[nodiscard]] consteval noexcept -> int {
        std::array test_input{9, 9, 7, 5, 4, 3, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0};
        static_assert(test_input.size() == 16UZ);

        return first_missing_positive(test_input.begin(), test_input.end());
    }()};

    STATIC_REQUIRE(std::same_as<int const, decltype(result)>);

    STATIC_REQUIRE(result == 6);
}
