// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/last-stone-weight/description/

#ifndef FORFUN_LAST_STONE_WEIGHT_HPP_
#define FORFUN_LAST_STONE_WEIGHT_HPP_

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
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

/// Assume each element (stone) of stones is non-negative, otherwise the
/// function's behavior is undefined.
template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
last_stone_weight(Iter const first, Sentinel end) noexcept
    -> std::iter_value_t<Iter>
{
    using ValueType = std::iter_value_t<Iter>;
    using DiffType = decltype(end - first);

    std::make_heap(first, end);

    auto size{end - first};

    while (size > DiffType{1})
    {
        auto s{*first};
        std::pop_heap(first, end--);

        s -= *first;
        std::pop_heap(first, end--);

        if (s != ValueType{0})
        {
            *end = s;
            ++end;
            std::push_heap(first, end);
        }

        size = end - first;
    }

    return size == DiffType{0} ? ValueType{0} : *first;
}

} // namespace heapified

namespace partially_sorted {

/// Assume stones is not empty, and each element (stone) of stones is
/// non-negative, otherwise the function's behavior is undefined.
template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
last_stone_weight(Iter const first, Sentinel end) noexcept
    -> std::iter_value_t<Iter>
{
    using ValueType = std::iter_value_t<Iter>;
    using DiffType = std::iter_difference_t<Iter>;

    assert(std::distance(first, end) > DiffType{0});

    if ((end - first) > ValueType{1})
    {
        auto iter{first};
        auto const sort_end{first + DiffType{2}};
        for (++iter; iter != end;)
        {
            std::partial_sort(first, sort_end, end, std::greater<>());

            *first -= *iter;
            *iter = *--end;
        }
    }

    return *first;
}

} // namespace partially_sorted

} // namespace forfun::last_stone_weight

#endif // FORFUN_LAST_STONE_WEIGHT_HPP_
