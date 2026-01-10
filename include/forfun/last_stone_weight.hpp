// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/last-stone-weight/

#ifndef FORFUN_LAST_STONE_WEIGHT_HPP_
#define FORFUN_LAST_STONE_WEIGHT_HPP_

#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <vector>

namespace forfun::last_stone_weight {

namespace naive {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of non-negative elements (weighs), otherwise the behavior of the
/// strategy is undefined.
template <std::contiguous_iterator IterA, std::bidirectional_iterator IterB>
    requires std::integral<std::iter_value_t<IterA>>
[[nodiscard]] constexpr auto
last_stone_weight(IterA const first, IterB last) noexcept
    -> std::iter_value_t<IterA>
{
    using ValueType = std::iter_value_t<IterA>;

    ValueType stone1{*first};

    for (auto stop{std::next(first)}; stop != last;)
    {
        ValueType stone2{};
        auto it_s1{last};
        auto it_s2{last};

        stone1 = ValueType{};

        // Find the heaviest two stones, where s1 is larger than or equal to s2.
        for (auto it{first}; it != last; ++it)
        {
            if (*it >= stone1)
            {
                stone2 = stone1;
                stone1 = *it;
                it_s2 = it_s1;
                it_s1 = it;
            }
            else if (*it >= stone2)
            {
                stone2 = *it;
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

        stone1 = *it_s1;
    }

    return stone1;
}

} // namespace naive

namespace heapified {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of non-negative elements (weighs), otherwise the behavior of the
/// strategy is undefined.
template <std::contiguous_iterator IterA, std::bidirectional_iterator IterB>
    requires std::integral<std::iter_value_t<IterA>>
[[nodiscard]] constexpr auto
last_stone_weight(IterA const first, IterB last) noexcept
    -> std::iter_value_t<IterA>
{
    using ValueType = std::iter_value_t<IterA>;
    using DiffType = decltype(last - first);

    std::make_heap(first, last);

    auto size{last - first};

    while (size > DiffType{1})
    {
        auto stone{*first};
        std::pop_heap(first, last--);

        stone -= *first;
        std::pop_heap(first, last--);

        if (stone != ValueType{})
        {
            *last = stone;
            ++last;
            std::push_heap(first, last);
        }

        size = last - first;
    }

    return size == DiffType{} ? ValueType{} : *first;
}

} // namespace heapified

namespace priority_queue_based {

/// @note The strategy assumes that @p stones is a non-empty vector of
/// non-negative elements (weighs), otherwise the behavior of the strategy is
/// undefined.
[[nodiscard]] auto last_stone_weight(std::vector<int>&& stones) -> int;

} // namespace priority_queue_based

namespace sort_based {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of non-negative elements (weighs), otherwise the behavior of the
/// strategy is undefined.
template <std::contiguous_iterator IterA, std::bidirectional_iterator IterB>
    requires std::sortable<IterA, std::greater<>>
    and std::integral<std::iter_value_t<IterA>>
[[nodiscard]] constexpr auto
last_stone_weight(IterA const first, IterB last) noexcept
    -> std::iter_value_t<IterA>
{
    auto second{std::next(first)};

    while (second != last)
    {
        std::sort(first, last, std::greater{});

        *first -= *second;
        *second = *--last;
    }

    return *first;
}

} // namespace sort_based

} // namespace forfun::last_stone_weight

#endif // FORFUN_LAST_STONE_WEIGHT_HPP_
