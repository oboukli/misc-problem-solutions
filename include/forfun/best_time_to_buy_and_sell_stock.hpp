// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#ifndef FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_
#define FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>

namespace forfun::best_time_to_buy_and_sell_stock {

namespace base {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements (prices), otherwise the behavior of the strategy is
/// undefined.
template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::same_as<int, std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
calc_max_profit(Iter iter, Sentinel const last) noexcept -> int
{
    int max_profit{0};

    auto buyer_iter{iter};
    while (++iter != last)
    {
        if (auto const profit{*iter - *buyer_iter}; profit < 0)
        {
            buyer_iter = iter;
        }
        else
        {
            max_profit = std::max(profit, max_profit);
        }
    }

    return max_profit;
}

} // namespace base

namespace optimized_l1 {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements (prices), otherwise the behavior of the strategy is
/// undefined.
template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::same_as<int, std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
calc_max_profit(Iter iter, Sentinel const last) noexcept -> int
{
    int max_profit{0};

    auto buyer_price{*iter};
    while (++iter != last)
    {
        auto const profit{*iter - buyer_price};

        if (profit < 0)
        {
            buyer_price = *iter;

            continue;
        }

        max_profit = std::max(profit, max_profit);
    }

    return max_profit;
}

} // namespace optimized_l1

namespace optimized_l2 {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements (prices), otherwise the behavior of the strategy is
/// undefined.
template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::same_as<int, std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
calc_max_profit(Iter iter, Sentinel const last) noexcept -> int
{
    int max_profit{0};

    auto buyer_price{*iter};
    while (++iter != last)
    {
        if (*iter < buyer_price)
        {
            buyer_price = *iter;

            continue;
        }

        max_profit = std::max(*iter - buyer_price, max_profit);
    }

    return max_profit;
}

} // namespace optimized_l2

} // namespace forfun::best_time_to_buy_and_sell_stock

#endif // FORFUN_BEST_TIME_TO_BUY_AND_SELL_STOCK_HPP_
