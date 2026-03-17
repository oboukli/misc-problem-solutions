// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/koko-eating-bananas/

#ifndef FORFUN_SEARCH_KOKO_EATING_BANANAS_HPP_
#define FORFUN_SEARCH_KOKO_EATING_BANANAS_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>

#include "forfun/common/math.hpp"

namespace forfun::search::koko_eating_bananas {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel>
    requires std::forward_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
    and std::same_as<std::iter_value_t<Iter>, int>
[[nodiscard]] constexpr auto min_eating_speed(
    Iter const first, Sentinel const last, int const duration
) noexcept -> int
{
    using std::max_element;
    using std::min;

    static constexpr int const one{1};
    static constexpr int const two{2};

    int min_speed{*max_element(first, last)};

    int lower{1};
    int upper{min_speed};

    while (lower <= upper)
    {
        int const speed{(lower + upper) / two};
        int time{0};

        for (auto iter{first}; iter != last; ++iter)
        {
            time += forfun::common::math::alternative::div_ceil(*iter, speed);
        }

        if (time <= duration)
        {
            min_speed = speed;
            upper = speed - one;
        }
        else
        {
            lower = speed + one;
        }
    }

    return min_speed;
}

} // namespace forfun::search::koko_eating_bananas

#endif // FORFUN_SEARCH_KOKO_EATING_BANANAS_HPP_
