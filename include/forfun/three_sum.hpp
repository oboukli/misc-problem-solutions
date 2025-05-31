// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// - https://en.wikipedia.org/wiki/3SUM
/// - https://leetcode.com/problems/3sum/

#ifndef FORFUN_THREE_SUM_HPP_
#define FORFUN_THREE_SUM_HPP_

#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace forfun::three_sum {

namespace presorted {

namespace two_pointer {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements that are sorted in non-descending order. Otherwise, the
/// behavior of the strategy is undefined.
template <std::forward_iterator IterA, std::bidirectional_iterator IterB>
    requires std::totally_ordered<std::iter_value_t<IterA>>
    and std::same_as<std::iter_value_t<IterA>, std::iter_value_t<IterB>>
[[nodiscard]] constexpr auto three_sum(IterA iter, IterB const last)
    -> std::vector<std::array<std::iter_value_t<IterA>, 3>>
{
    using DiffType = std::iter_difference_t<IterA>;
    using ValueType = std::iter_value_t<IterA>;

    std::vector<std::array<ValueType, 3>> result{};

    auto const last_i{std::next(iter, std::distance(iter, last) - 2)};
    for (auto prev_i{last}; iter != last_i; ++iter)
    {
        if (std::greater{}(*iter, ValueType{0}))
        {
            break;
        }

        if ((prev_i != last) && (std::equal_to{}(*prev_i, *iter)))
        {
            continue;
        }

        prev_i = iter;

        auto const target{std::minus{}(ValueType{0}, *iter)};
        auto iter_j{std::next(iter)};
        auto iter_k{last};
        --iter_k;
        while (std::distance(iter_j, iter_k) > DiffType{0})
        {
            if (auto const addend{std::plus{}(*iter_j, *iter_k)};
                std::equal_to{}(target, addend))
            {
                auto const val_j{*iter_j};
                auto const val_k{*iter_k};
                result.emplace_back(std::array{*iter, val_j, val_k});
                ++iter_j;
                --iter_k;
                while ((std::distance(iter_j, iter_k) > DiffType{0})
                       && (std::equal_to{}(val_j, *iter_j)))
                {
                    ++iter_j;
                }

                while ((std::distance(iter_j, iter_k) > DiffType{0})
                       && (std::equal_to{}(val_k, *iter_k)))
                {
                    --iter_k;
                }
            }
            else if (std::less{}(target, addend))
            {
                --iter_k;
            }
            else
            {
                ++iter_j;
            }
        }
    }

    return result;
}

} // namespace two_pointer

namespace set_map_based {

namespace detail {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::equality_comparable<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto find(
    Iter iter,
    Sentinel const last,
    Iter const iter_a,
    Iter const iter_b,
    std::iter_value_t<Iter> const target
) -> Iter
{
    // std::lower_bound can be written once, but we leave it to the compiler to
    // optimize it.
    iter = std::lower_bound(iter, last, target);
    for (; iter != last; iter = std::lower_bound(++iter, last, target))
    {
        if (std::not_equal_to{}(*iter, target))
        {
            return last;
        }

        if ((iter != iter_a) && (iter != iter_b))
        {
            return iter;
        }
    }

    return last;
}

template <std::totally_ordered T>
constexpr auto resort(T const a, T const b, T const c) noexcept
    -> std::array<T, 3>
{
    if (std::less{}(c, a))
    {
        return {c, a, b};
    }

    if (std::less{}(b, c))
    {
        return {a, b, c};
    }

    return {a, c, b};
}

} // namespace detail

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements that are sorted in non-descending order. Otherwise, the
/// behavior of the strategy is undefined.
template <std::forward_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::totally_ordered<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto three_sum(Iter const first, Sentinel const last)
    -> std::vector<std::array<std::iter_value_t<Iter>, 3>>
{
    using ValueType = std::iter_value_t<Iter>;

    std::vector<std::array<ValueType, 3>> result{};
    std::map<ValueType, std::set<ValueType>> m{};

    // We do not utilize std::prev because it does not work with
    // std::forward_iterator.
    // clang-format off
    for (auto iter_a{first};
        iter_a != std::next(first, std::distance(first, last) - 1);
        ++iter_a)
    // clang-format on
    {
        if (std::greater{}(*iter_a, ValueType{0}))
        {
            break;
        }

        if (iter_a != first
            && std::equal_to{}(
                *iter_a, *std::next(first, std::distance(first, iter_a) - 1)
            ))
        {
            continue;
        }

        for (auto iter_b{std::next(iter_a)}; iter_b != last; ++iter_b)
        {
            if (iter_b != std::next(iter_a)
                && std::equal_to{}(
                    *iter_b,
                    *std::next(iter_a, std::distance(iter_a, iter_b) - 1)
                ))
            {
                continue;
            }

            ValueType const target{
                std::minus{}(ValueType{0}, std::plus{}(*iter_a, *iter_b))
            };

            if (auto const iter_c
                = detail::find(first, last, iter_a, iter_b, target);
                iter_c != last)
            {
                auto const a{detail::resort(*iter_a, *iter_b, *iter_c)};
                auto const iter_map_entry{
                    m.emplace(a.front(), std::initializer_list<ValueType>{})
                        .first
                };

                if (iter_map_entry->second.insert(a[1]).second)
                {
                    result.emplace_back(a);
                }
            }
        }
    }

    return result;
}

} // namespace set_map_based

} // namespace presorted

namespace non_presorted {

namespace detail {

template <std::totally_ordered T>
constexpr auto make_sorted_array(T const a, T const b, T const c) noexcept
    -> std::array<T, 3>
{
    if (std::less{}(a, b))
    {
        if (std::less{}(b, c))
        {
            return {a, b, c};
        }

        if (std::less{}(a, c))
        {
            return {a, c, b};
        }

        return {c, a, b};
    }

    if (std::less{}(a, c))
    {
        return {b, a, c};
    }

    if (std::less{}(b, c))
    {
        return {b, c, a};
    }

    return {c, b, a};
}

} // namespace detail

namespace brute_force {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <std::forward_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::totally_ordered<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto three_sum(Iter const first, Sentinel const last)
    -> std::vector<std::array<std::iter_value_t<Iter>, 3>>
{
    using ValueType = std::iter_value_t<Iter>;
    using MapType = std::vector<std::pair<ValueType, ValueType>>;

    std::vector<std::array<ValueType, 3>> result{};

    MapType pair_map{};
    pair_map.reserve(
        static_cast<MapType::size_type>(std::distance(first, last))
    );

    // We do not utilize std::prev so it is enough to satisfy
    // std::forward_iterator.
    auto const last_i{std::next(first, std::distance(first, last) - 2)};
    auto const last_j{std::next(first, std::distance(first, last) - 1)};
    for (auto iter_i{first}; iter_i != last_i; ++iter_i)
    {
        for (auto iter_j{std::next(iter_i)}; iter_j != last_j; ++iter_j)
        {
            auto const a{std::plus{}(*iter_i, *iter_j)};
            for (auto iter_k{std::next(iter_j)}; iter_k != last; ++iter_k)
            {
                if (std::equal_to{}(std::plus{}(a, *iter_k), ValueType{0}))
                {
                    auto const tri{
                        detail::make_sorted_array(*iter_i, *iter_j, *iter_k)
                    };

                    if (std::find(
                            pair_map.cbegin(),
                            pair_map.cend(),
                            std::pair{tri.front(), tri[1UZ]}
                        )
                        == pair_map.cend())
                    {
                        pair_map.emplace_back(std::pair{tri.front(), tri[1UZ]});

                        result.emplace_back(tri);
                    }
                }
            }
        }
    }

    return result;
}

} // namespace brute_force

namespace set_based {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <std::forward_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::totally_ordered<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto three_sum(Iter const first, Sentinel const last)
    -> std::vector<std::array<std::iter_value_t<Iter>, 3>>
{
    using ValueType = std::iter_value_t<Iter>;

    std::set<std::array<ValueType, 3>> unique_prefixes{};
    auto const last_i{std::next(first, std::distance(first, last) - 2)};
    for (auto iter_i{first}; iter_i != last_i; ++iter_i)
    {
        auto const minuend{std::minus{}(ValueType{0}, *iter_i)};

        auto const last_j{std::next(first, std::distance(first, last) - 1)};
        for (auto iter_j{std::next(iter_i)}; iter_j != last_j; ++iter_j)
        {
            auto const target{std::minus{}(minuend, *iter_j)};

            for (auto iter_k{std::next(iter_j)}; iter_k != last; ++iter_k)
            {
                if (std::equal_to{}(*iter_k, target))
                {
                    unique_prefixes.emplace(
                        detail::make_sorted_array(*iter_i, *iter_j, *iter_k)
                    );

                    break;
                }
            }
        }
    }

    return std::vector<std::array<ValueType, 3>>(
        unique_prefixes.cbegin(), unique_prefixes.cend()
    );
}

} // namespace set_based

} // namespace non_presorted

} // namespace forfun::three_sum

#endif // FORFUN_THREE_SUM_HPP_
