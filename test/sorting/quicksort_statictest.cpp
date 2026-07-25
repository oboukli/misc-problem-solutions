// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sorting/quicksort.hpp"

TEST_CASE("Quicksort sort", "[sorting][quicksort]")
{
    using forfun::sorting::quicksort;

    SECTION("One element")
    {
        static constexpr auto result{
            [] [[nodiscard]] consteval noexcept -> bool {
                std::array actual{7};
                static constexpr std::array const expected{7};

                quicksort(actual.begin(), actual.end());

                return (actual.size() == 1UZ)
                    && (actual.size() == expected.size())
                    && (actual.front() == expected.front());
            }()
        };

        STATIC_REQUIRE(result);
    }

    SECTION("Three elements")
    {
        static constexpr auto result{
            [] [[nodiscard]] consteval noexcept -> bool {
                std::array actual{5, 3, 4};
                static constexpr std::array const expected{3, 4, 5};

                quicksort(actual.begin(), actual.end());

                return (actual.size() == 3UZ)
                    && (actual.size() == expected.size())
                    && (actual.front() == expected.front())
                    && (actual.at(1) == expected.at(1))
                    && (actual.at(2) == expected.at(2));
            }()
        };

        STATIC_REQUIRE(result);
    }
}
