// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/last-stone-weight/description/

#ifndef FORFUN_LAST_STONE_WEIGHT_HPP_
#define FORFUN_LAST_STONE_WEIGHT_HPP_

#include <cassert>
#include <concepts>
#include <iterator>

namespace forfun::last_stone_weight {

namespace naive {

/// Assume stones is not empty, and each element (stone) of stones is
/// non-negative, otherwise the function's behavior is undefined.
template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
last_stone_weight(Iter const first, Sentinel end) noexcept
    -> std::iter_value_t<Iter>
{
    using ValueType = std::iter_value_t<Iter>;

    assert((end - first) != decltype(end - first){0});

    ValueType s1{*first};
    auto stop{first};
    for (++stop; stop != end;)
    {
        ValueType s2{0};
        auto it_s1{end};
        auto it_s2{end};

        s1 = ValueType{0};

        // Find the heaviest two stones, where s1 is larger than or equal to s2.
        for (auto it{first}; it != end; ++it)
        {
            if (*it >= s1)
            {
                s2 = s1;
                s1 = *it;
                it_s2 = it_s1;
                it_s1 = it;
            }
            else if (*it >= s2)
            {
                s2 = *it;
                it_s2 = it;
            }
        }

        assert(it_s1 != end);
        assert(it_s2 != end);

        // Smash the two stones together.
        *it_s1 -= *it_s2;
        --end;
        if (stop != end)
        {
            *it_s2 = *end;
        }

        s1 = *it_s1;
    }

    return s1;
}

} // namespace naive

namespace heapified {

// Placeholder.

} // namespace heapified

} // namespace forfun::last_stone_weight

#endif // FORFUN_LAST_STONE_WEIGHT_HPP_
