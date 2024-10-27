// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

#ifndef FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_
#define FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_

#include <algorithm>
#include <span>

namespace forfun::best_time_to_buy_and_sell_stock {

[[nodiscard]] constexpr auto
calc_max_profit(std::span<int const> const prices) noexcept -> int
{
    if (prices.size() < decltype(prices)::size_type{2U})
    {
        return 0;
    }

    int max_profit{0};
    auto buyer_iter{prices.begin()}; // Could be refactored to use C++23 cbegin
    auto seller_iter{buyer_iter};
    ++seller_iter;
    auto const end{prices.end()};

    for (; seller_iter != end; ++seller_iter)
    {
        auto const profit{*seller_iter - *buyer_iter};

        if (profit < 0)
        {
            buyer_iter = seller_iter;

            continue;
        }

        max_profit = std::max(profit, max_profit);
    }

    return max_profit;
}

namespace optimized_l1 {
[[nodiscard]] constexpr auto
calc_max_profit(std::span<int const> const prices) noexcept -> int
{
    auto seller_iter{prices.begin()};
    auto const end{prices.end()};

    if (seller_iter == end)
    {
        return 0;
    }

    auto buyer_price{prices.front()}; // Could be refactored to use C++23 cbegin
    int max_profit{0};

    for (++seller_iter; seller_iter != end; ++seller_iter)
    {
        auto const profit{*seller_iter - buyer_price};

        if (profit < 0)
        {
            buyer_price = *seller_iter;

            continue;
        }

        max_profit = std::max(profit, max_profit);
    }

    return max_profit;
}

} // namespace optimized_l1

namespace optimized_l2 {
[[nodiscard]] constexpr auto
calc_max_profit(std::span<int const> const prices) noexcept -> int
{
    auto seller_iter{prices.begin()}; // Could be refactored to use C++23 cbegin
    auto const end{prices.end()};

    if (seller_iter == end)
    {
        return 0;
    }

    auto buyer_price{prices.front()};
    int max_profit{0};

    for (++seller_iter; seller_iter != end; ++seller_iter)
    {
        if (*seller_iter < buyer_price)
        {
            buyer_price = *seller_iter;

            continue;
        }

        max_profit = std::max(*seller_iter - buyer_price, max_profit);
    }

    return max_profit;
}

} // namespace optimized_l2

} // namespace forfun::best_time_to_buy_and_sell_stock

#endif // FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_
