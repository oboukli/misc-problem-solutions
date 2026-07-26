// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/tower_of_hanoi.hpp"

TEST_CASE("Tower of Hanoi", "[tower_of_hanoi]")
{
    SECTION("Two disks")
    {
        static constexpr auto result{
            [] [[nodiscard]] consteval noexcept -> bool {
                static constexpr std::size_t const num_disks{2};

                int src_rod{2};
                int des_rod{};
                int aux_rod{};

                forfun::tower_of_hanoi::recursive::toh(
                    src_rod,
                    des_rod,
                    aux_rod,
                    [](int& src, int& des) consteval noexcept -> void {
                        --src;
                        ++des;
                    },
                    num_disks
                );

                return (src_rod == 0) && (des_rod == 2) && (aux_rod == 0);
            }()
        };

        STATIC_REQUIRE(result);
    }

    SECTION("Exception specification")
    {
        SECTION("noexcept(false)")
        {
            STATIC_REQUIRE_FALSE(
                noexcept(forfun::tower_of_hanoi::recursive::toh(
                    std::declval<int&>(),
                    std::declval<int&>(),
                    std::declval<int&>(),
                    [] [[noreturn]] (int&, int&) -> void { throw; },
                    0
                ))
            );
        }

        SECTION("noexcept(true)")
        {
            STATIC_REQUIRE(
                noexcept(forfun::tower_of_hanoi::recursive::toh(
                    std::declval<int&>(),
                    std::declval<int&>(),
                    std::declval<int&>(),
                    [](int&, int&) noexcept -> void {},
                    0
                ))
            );
        }
    }
}
