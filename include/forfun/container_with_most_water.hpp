// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/container-with-most-water/

#ifndef FORFUN_CONTAINER_WITH_MOST_WATER_HPP_
#define FORFUN_CONTAINER_WITH_MOST_WATER_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::container_with_most_water {

namespace brute {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] auto calc_max_area(Iter iter_a, Sentinel const last) noexcept
    -> int
{
    int max_area{0};

    for (; iter_a != last; ++iter_a)
    {
        int width{1};
        for (auto iter_b{std::next(iter_a)}; iter_b != last; ++iter_b, ++width)
        {
            int const height{std::min(*iter_a, *iter_b)};
            int const area{height * width};

            max_area = std::max(area, max_area);
        }
    }

    return max_area;
}

} // namespace brute

namespace enhanced {

template <std::forward_iterator IterA, std::bidirectional_iterator IterB>
[[nodiscard]] auto calc_max_area(IterA iter_a, IterB iter_b) noexcept -> int
{
    int max_area{0};

    --iter_b;
    int width{static_cast<int>(std::distance(iter_a, iter_b))};

    while (iter_a != iter_b)
    {
        int const height{std::min(*iter_a, *iter_b)};
        int const area{height * width};

        max_area = std::max(area, max_area);

        if (*iter_a < *iter_b)
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
