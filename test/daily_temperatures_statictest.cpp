// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <concepts>

#include <catch2/catch_test_macros.hpp>

#include "forfun/daily_temperatures.hpp"

TEST_CASE("Daily temperatures", "[daily_temperatures]")
{
    static constexpr auto result{[] [[nodiscard]] consteval noexcept -> bool {
        static constexpr std::array const temperatures{15, 13, 16};
        std::array<int, 3> day_counts{};
        std::array<decltype(temperatures)::difference_type, 3> scratch{};

        forfun::daily_temperatures::daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        auto const [a, b, c] = day_counts;

        return (a == 2) && (b == 1) && (c == 0);
    }()};

    STATIC_REQUIRE(std::same_as<bool const, decltype(result)>);
    STATIC_REQUIRE(result);
}
