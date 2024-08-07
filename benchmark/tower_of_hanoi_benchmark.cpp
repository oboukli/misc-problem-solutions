// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/tower_of_hanoi.hpp"

TEST_CASE("Tower of Hanoi benchmarking", "[benchmark][tower_of_hanoi]")
{
    using namespace forfun::tower_of_hanoi;

    using Rod = int;
    using Monk = decltype([](Rod&, Rod&) noexcept -> void {});

    ankerl::nanobench::Bench()

        .title("Tower of Hanoi")
        .relative(true)

        .run(
            NAMEOF_RAW(recursive::toh<Rod, Monk, std::size_t>).c_str(),
            []() {
                static constexpr std::size_t const num_disks{4};
                // NOLINTBEGIN(misc-const-correctness)
                Rod src{};
                Rod des{};
                Rod aux{};
                // NOLINTEND(misc-const-correctness)

                forfun::tower_of_hanoi::recursive::toh(
                    src, des, aux, [](Rod&, Rod&) noexcept -> void {}, num_disks
                );

                ankerl::nanobench::doNotOptimizeAway(des);
            }
        )

        ;
}
