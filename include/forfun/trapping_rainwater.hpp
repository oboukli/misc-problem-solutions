// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/trapping-rain-water/
/// https://neetcode.io/problems/trapping-rain-water/

#ifndef FORFUN_TRAPPING_RAIN_WATER_HPP_
#define FORFUN_TRAPPING_RAIN_WATER_HPP_

#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>

namespace forfun::trapping_rainwater {

/// Time complexity: O(n)
/// Space complexity: O(1)
/// @note The strategy assumes that @p lhs_iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter>
// clang-format off
    requires std::bidirectional_iterator<Iter>
    and (std::signed_integral<std::iter_value_t<Iter>>
        or std::floating_point<std::iter_value_t<Iter>>)
// clang-format on
[[nodiscard]] constexpr auto trap(Iter lhs_iter, Iter const last) noexcept
    -> std::iter_value_t<Iter>
{
    using std::less;
    using std::max;
    using std::minus;

    using ValueType = std::iter_value_t<Iter>;

    ValueType total_capacity{};

    Iter rhs_iter{std::prev(last)};

    ValueType max_left{*lhs_iter};
    ValueType max_right{*rhs_iter};

    while (lhs_iter != rhs_iter)
    {
        if (less{}(max_left, max_right))
        {
            ValueType const elevation{*(++lhs_iter)};

            total_capacity += max(minus{}(max_left, elevation), {});

            max_left = max(max_left, elevation);
        }
        else
        {
            ValueType const elevation{*(--rhs_iter)};

            total_capacity += max(minus{}(max_right, elevation), {});

            max_right = max(elevation, max_right);
        }
    }

    return total_capacity;
}

} // namespace forfun::trapping_rainwater

#endif // FORFUN_TRAPPING_RAIN_WATER_HPP_
