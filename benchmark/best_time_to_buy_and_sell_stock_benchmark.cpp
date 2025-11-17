// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/best_time_to_buy_and_sell_stock.hpp"

TEST_CASE(
    "Best time to buy and sell stock benchmarking",
    "[benchmark][best_time_to_buy_and_sell_stock]"
)
{
    using namespace forfun;
    using Iter = std::vector<int>::const_iterator;

    std::vector const prices{
        2,   5,   11,  17,  23,  29,  41,  47,  53,  59,  71,
        83,  89,  101, 107, 113, 131, 137, 149, 167, 173, 179,
        191, 197, 227, 233, 239, 251, 257, 263, 269, 271,
    };

    ankerl::nanobench::Bench()

        .title("Best time to buy and sell stock")
        .relative(true)

        .run(
            NAMEOF_RAW(
                best_time_to_buy_and_sell_stock::base::
                    calc_max_profit<Iter, Iter>
            )
                .c_str(),
            [&prices] noexcept -> void {
                auto const volatile r{
                    best_time_to_buy_and_sell_stock::base::calc_max_profit(
                        prices.cbegin(), prices.cend()
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                best_time_to_buy_and_sell_stock::optimized_l1::
                    calc_max_profit<Iter, Iter>
            )
                .c_str(),
            [&prices] noexcept -> void {
                auto const volatile r{
                    best_time_to_buy_and_sell_stock::optimized_l1::
                        calc_max_profit(prices.cbegin(), prices.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                best_time_to_buy_and_sell_stock::optimized_l2::
                    calc_max_profit<Iter, Iter>
            )
                .c_str(),
            [&prices] noexcept -> void {
                auto const volatile r{
                    best_time_to_buy_and_sell_stock::optimized_l2::
                        calc_max_profit(prices.cbegin(), prices.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
