// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/contains-duplicate/

#ifndef FORFUN_CONTAINS_DUPLICATE_HPP_
#define FORFUN_CONTAINS_DUPLICATE_HPP_

#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <utility>

namespace forfun::contains_duplicate {

namespace quadratic {

template <
    std::forward_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    std::equivalence_relation<std::iter_value_t<Iter>, std::iter_value_t<Iter>>
        BinaryPredicate>
[[nodiscard]] constexpr auto
contains_duplicate(Iter iter, Sentinel const last, BinaryPredicate eq) noexcept(
    noexcept(eq.operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    for (; iter != last; ++iter)
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
    }

    return false;
}

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<std::iter_value_t<Iter>>>().operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(
        first, last, std::equal_to<std::iter_value_t<Iter>>{}
    );
}

} // namespace quadratic

namespace sorted {

template <
    std::random_access_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    std::equivalence_relation<std::iter_value_t<Iter>, std::iter_value_t<Iter>>
        BinaryPredicate>
[[nodiscard]] constexpr auto
contains_duplicate(Iter iter, Sentinel const last, BinaryPredicate eq) noexcept(
    noexcept(eq.operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    if (iter == last) [[unlikely]]
    {
        return false;
    }

    std::sort(iter, last);

    for (auto iter_next{iter}; ++iter_next != last; iter = iter_next)
    {
        if (eq(*iter, *iter_next))
        {
            return true;
        }
    }

    return false;
}

template <std::random_access_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<std::iter_value_t<Iter>>>().operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(
        first, last, std::equal_to<std::iter_value_t<Iter>>{}
    );
}

} // namespace sorted

namespace stl {

template <
    std::random_access_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    std::equivalence_relation<std::iter_value_t<Iter>, std::iter_value_t<Iter>>
        BinaryPredicate>
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

template <std::random_access_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] constexpr auto
contains_duplicate(Iter const first, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<std::iter_value_t<Iter>>>().operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(
        first, last, std::equal_to<std::iter_value_t<Iter>>{}
    );
}

} // namespace stl

} // namespace forfun::contains_duplicate

#endif // FORFUN_CONTAINS_DUPLICATE_HPP_
