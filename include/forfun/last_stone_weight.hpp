// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/last-stone-weight/description/

#ifndef FORFUN_LAST_STONE_WEIGHT_HPP_
#define FORFUN_LAST_STONE_WEIGHT_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>
#include <vector>

namespace forfun::last_stone_weight {

namespace naive {

/// Assume stones is not empty, and each element (stone) of stones is
/// non-negative, otherwise the function's behavior is undefined.
template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
last_stone_weight(Iter const first, Sentinel last) noexcept
    -> std::iter_value_t<Iter>
{
    using ValueType = std::iter_value_t<Iter>;

    if (first == last)
    {
        return ValueType{0};
    }

    ValueType s1{*first};
    auto stop{first};
    for (++stop; stop != last;)
    {
        ValueType s2{0};
        auto it_s1{last};
        auto it_s2{last};

        s1 = ValueType{0};

        // Find the heaviest two stones, where s1 is larger than or equal to s2.
        for (auto it{first}; it != last; ++it)
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

        // Smash the two stones together.
        *it_s1 -= *it_s2;
        --last;
        if (stop != last)
        {
            *it_s2 = *last;
        }

        s1 = *it_s1;
    }

    return s1;
}

} // namespace naive

namespace heapified {

/// Assume each element (stone) of stones is non-negative, otherwise the
/// function's behavior is undefined.
template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
last_stone_weight(Iter const first, Sentinel last) noexcept
    -> std::iter_value_t<Iter>
{
    using ValueType = std::iter_value_t<Iter>;
    using DiffType = decltype(last - first);

    std::make_heap(first, last);

    auto size{last - first};

    while (size > DiffType{1})
    {
        auto s{*first};
        std::pop_heap(first, last--);

        s -= *first;
        std::pop_heap(first, last--);

        if (s != ValueType{0})
        {
            *last = s;
            ++last;
            std::push_heap(first, last);
        }

        size = last - first;
    }

    return size == DiffType{0} ? ValueType{0} : *first;
}

} // namespace heapified

namespace priority_queue_based {

/// Assume each element (stone) of stones is non-negative, otherwise the
/// function's behavior is undefined.
[[nodiscard]] auto last_stone_weight(std::vector<int>&& stones) noexcept -> int;

} // namespace priority_queue_based

} // namespace forfun::last_stone_weight

#endif // FORFUN_LAST_STONE_WEIGHT_HPP_
