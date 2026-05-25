// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/search/minimum_rotated_element.hpp"

TEST_CASE(
    "Find minimum in rotated sorted array benchmarking",
    "[benchmark][minimum_rotated_element]"
)
{
    static constexpr std::array const elements{
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

    using ConstIter = decltype(elements)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Find minimum in rotated sorted array")
        .relative(true)

        .run(
            NAMEOF_RAW(
                forfun::search::minimum_rotated_element::iterative::
                    find_min<ConstIter, ConstIter>
            )
                .c_str(),
            [] noexcept -> void {
                auto const volatile r{
                    forfun::search::minimum_rotated_element::iterative::
                        find_min(elements.cbegin(), elements.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                forfun::search::minimum_rotated_element::recursive::
                    find_min<ConstIter, ConstIter>
            )
                .c_str(),
            [] noexcept -> void {
                auto const volatile r{
                    forfun::search::minimum_rotated_element::recursive::
                        find_min(elements.cbegin(), elements.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
