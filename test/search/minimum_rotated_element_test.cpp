// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/minimum_rotated_element.hpp"

namespace {

using CIter = std::vector<int>::const_iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Find minimum in rotated sorted array",
    "[minimum_rotated_element]",
    (auto find_min, find_min),
    // clang-format off
    (forfun::search::minimum_rotated_element::iterative::
        find_min<CIter, CIter>),
    // clang-format on
    (forfun::search::minimum_rotated_element::recursive::find_min<CIter, CIter>)
)
{
    SECTION("One element")
    {
        std::vector const elements{19};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 19);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Two elements")
    {
        std::vector const elements{5519, 5521};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 5519);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Two elements rotated once")
    {
        std::vector const elements{929, 919};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 919);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Three elements")
    {
        std::vector const elements{6101, 6113, 6121};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 6101);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Three elements rotated once")
    {
        std::vector const elements{6121, 6101, 6113};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 6101);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Three elements rotated twice")
    {
        std::vector const elements{6113, 6121, 6101};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 6101);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Four elements")
    {
        std::vector const elements{7001, 7013, 7019, 7027};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 7001);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Four elements rotated once")
    {
        std::vector const elements{7027, 7001, 7013, 7019};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 7001);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Four elements rotated twice")
    {
        std::vector const elements{7019, 7027, 7001, 7013};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 7001);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Four elements rotated three times")
    {
        std::vector const elements{7013, 7019, 7027, 7001};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 7001);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements")
    {
        std::vector const elements{-6, -5, -1, 0, 60};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == -6);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements rotated once")
    {
        std::vector const elements{60, -6, -5, -1, 0};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == -6);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements rotated twice")
    {
        std::vector const elements{0, 60, -6, -5, -1};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == -6);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements rotated three times")
    {
        std::vector const elements{-1, 0, 60, -6, -5};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == -6);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements rotated four times")
    {
        std::vector const elements{-5, -1, 0, 60, -6};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == -6);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Five elements rotated three times (LeetCode case 1)")
    {
        std::vector const elements{3, 4, 5, 1, 2};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 1);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("LeetCode case 2")
    {
        std::vector const elements{4, 5, 6, 7, 0, 1, 2};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 0);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("LeetCode case 3")
    {
        std::vector const elements{11, 13, 15, 17};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 11);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("NeetCode case 1")
    {
        std::vector const elements{3, 4, 5, 6, 1, 2};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 1);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("NeetCode case 2")
    {
        std::vector const elements{4, 5, 0, 1, 2, 3};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 0);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("NeetCode case 3")
    {
        std::vector const elements{4, 5, 6, 7};

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 4);

        REQUIRE(result == std::ranges::min_element(elements));
    }

    SECTION("Sixty-four elements rotated eight times (benchmark case)")
    {
        std::vector const elements{
            // clang-format off
            8093, 8101, 8111, 8117, 8123, 8147, 8161, 8167,
            7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639,
            7643, 7649, 7669, 7673, 7681, 7687, 7691, 7699,
            7703, 7717, 7723, 7727, 7741, 7753, 7757, 7759,
            7789, 7793, 7817, 7823, 7829, 7841, 7853, 7867,
            7873, 7877, 7879, 7883, 7901, 7907, 7919, 7927,
            7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011,
            8017, 8039, 8053, 8059, 8069, 8081, 8087, 8089,
            // clang-format on
        };

        CAPTURE(elements);

        auto const result{find_min(elements.cbegin(), elements.cend())};

        REQUIRE_FALSE(result == elements.cend());

        REQUIRE(*result == 7577);

        REQUIRE(result == std::ranges::min_element(elements));
    }
}
