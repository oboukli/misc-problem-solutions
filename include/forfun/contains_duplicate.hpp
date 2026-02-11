// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/contains-duplicate/

#ifndef FORFUN_CONTAINS_DUPLICATE_HPP_
#define FORFUN_CONTAINS_DUPLICATE_HPP_

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <functional>
#include <iterator>
#include <unordered_set>
#include <utility>

namespace forfun::contains_duplicate {

namespace quadratic {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel, typename BinaryPredicate>
// clang-format off
    requires std::forward_iterator<Iter>
    and std::sentinel_for<Sentinel, Iter>
    and std::equivalence_relation<
        BinaryPredicate,
        std::iter_value_t<Iter>,
        std::iter_value_t<Iter>>
// clang-format on
[[nodiscard]] constexpr auto
contains_duplicate(Iter iter, Sentinel const last, BinaryPredicate eq) noexcept(
    noexcept(eq.operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        auto const val{*iter};
        auto iter_next{iter};
        while (++iter_next != last)
        {
            if (eq(*iter_next, val))
            {
                return true;
            }
        }
        ++iter;
    } while (iter != last);

    return false;
}

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel>
    requires std::forward_iterator<Iter> and std::sentinel_for<Sentinel, Iter>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<>>()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(first, last, std::equal_to{});
}

} // namespace quadratic

namespace sorted {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel, typename BinaryPredicate>
// clang-format off
    requires std::random_access_iterator<Iter>
    and std::sentinel_for<Sentinel, Iter>
    and std::equivalence_relation<
        BinaryPredicate,
        std::iter_value_t<Iter>,
        std::iter_value_t<Iter>>
// clang-format on
[[nodiscard]] constexpr auto
contains_duplicate(Iter iter, Sentinel const last, BinaryPredicate eq) noexcept(
    noexcept(eq.operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    std::sort(iter, last);

    for (auto iter_next{std::next(iter)}; iter_next != last; ++iter_next)
    {
        if (eq(*iter, *iter_next))
        {
            return true;
        }

        iter = iter_next;
    }

    return false;
}

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel>
    requires std::random_access_iterator<Iter>
    and std::sentinel_for<Sentinel, Iter>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<>>()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(first, last, std::equal_to{});
}

} // namespace sorted

namespace adjacent_find_based {

template <typename Iter, typename Sentinel, typename BinaryPredicate>
// clang-format off
    requires std::random_access_iterator<Iter>
    and std::sentinel_for<Sentinel, Iter>
    and std::equivalence_relation<
        BinaryPredicate,
        std::iter_value_t<Iter>,
        std::iter_value_t<Iter>>
// clang-format on
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last, BinaryPredicate eq)
    // clang-format off
    noexcept(
        noexcept(eq.operator()(
            std::declval<std::iter_value_t<Iter>>(),
            std::declval<std::iter_value_t<Iter>>()
        )))
    // clang-format on
    -> bool
{
    std::sort(first, last);

    return std::adjacent_find(first, last, eq) != last;
}

template <typename Iter, typename Sentinel>
    requires std::random_access_iterator<Iter>
    and std::sentinel_for<Sentinel, Iter>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<>>()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(first, last, std::equal_to{});
}

} // namespace adjacent_find_based

namespace unordered_set_based {

template <typename Iter, typename Sentinel, typename BinaryPredicate>
// clang-format off
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::equivalence_relation<
        BinaryPredicate,
        std::iter_value_t<Iter>,
        std::iter_value_t<Iter>>
// clang-format on
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last, BinaryPredicate eq)
    -> bool
{
    using std::distance;
    using std::hash;

    using ValueType = std::iter_value_t<Iter>;

    std::unordered_set<ValueType, hash<ValueType>, BinaryPredicate> tracker(
        static_cast<std::size_t>(distance(first, last)), hash<ValueType>{}, eq
    );

    for (auto iter{first}; iter != last; ++iter)
    {
        if (auto const result{tracker.insert(*iter)}; not result.second)
        {
            return true;
        }
    }

    return false;
}

template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<>>()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(first, last, std::equal_to{});
}

} // namespace unordered_set_based

} // namespace forfun::contains_duplicate

#endif // FORFUN_CONTAINS_DUPLICATE_HPP_
