// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/container-with-most-water/

#ifndef FORFUN_CONTAINER_WITH_MOST_WATER_HPP_
#define FORFUN_CONTAINER_WITH_MOST_WATER_HPP_

#include <algorithm>
#include <functional>
#include <iterator>

namespace forfun::container_with_most_water {

namespace brute {

template <typename Iter, typename Sentinel>
    requires std::forward_iterator<Iter> and std::sentinel_for<Iter, Sentinel>
[[nodiscard]] constexpr auto
calc_max_area(Iter iter_a, Sentinel const last) noexcept -> int
{
    using std::max;
    using std::min;
    using std::multiplies;
    using std::next;

    int max_area{};

    for (; iter_a != last; ++iter_a)
    {
        int width{1};
        for (auto iter_b{next(iter_a)}; iter_b != last; ++iter_b, ++width)
        {
            int const height{min(*iter_a, *iter_b)};
            int const area{multiplies{}(height, width)};

            max_area = max(area, max_area);
        }
    }

    return max_area;
}

} // namespace brute

namespace enhanced {

template <typename Iter>
    requires std::contiguous_iterator<Iter>
[[nodiscard]] constexpr auto calc_max_area(Iter iter_a, Iter iter_b) noexcept
    -> int
{
    using std::distance;
    using std::less;
    using std::max;
    using std::min;
    using std::multiplies;

    int max_area{};

    --iter_b;
    int width{static_cast<int>(distance(iter_a, iter_b))};

    while (iter_a != iter_b)
    {
        int const height{min(*iter_a, *iter_b)};
        int const area{multiplies{}(height, width)};

        max_area = max(area, max_area);

        if (less{}(*iter_a, *iter_b))
        {
            ++iter_a;
        }
        else
        {
            --iter_b;
        }

        --width;
    }

    return max_area;
}

} // namespace enhanced

} // namespace forfun::container_with_most_water

#endif // FORFUN_CONTAINER_WITH_MOST_WATER_HPP_
