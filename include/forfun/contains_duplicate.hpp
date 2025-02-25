// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/contains-duplicate/

#ifndef FORFUN_CONTAINS_DUPLICATE_HPP_
#define FORFUN_CONTAINS_DUPLICATE_HPP_

#include <concepts>
#include <functional>
#include <iterator>
#include <utility>

namespace forfun::contains_duplicate {

template <
    std::forward_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    std::equivalence_relation<std::iter_value_t<Iter>, std::iter_value_t<Iter>>
        BinaryPredicate>
[[nodiscard]] constexpr auto
contains_duplicate(Iter itr, Sentinel const last, BinaryPredicate eq) noexcept(
    noexcept(eq.operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    for (; itr != last; ++itr)
    {
        auto const val{*itr};
        auto it_j{itr};
        for (++it_j; it_j != last; ++it_j)
        {
            if (eq(*it_j, val))
            {
                return true;
            }
        }
    }

    return false;
}

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] constexpr auto
contains_duplicate(Iter itr, Sentinel const last) noexcept(
    noexcept(std::declval<std::equal_to<std::iter_value_t<Iter>>>().operator()(
        std::declval<std::iter_value_t<Iter>>(),
        std::declval<std::iter_value_t<Iter>>()
    ))
) -> bool
{
    return contains_duplicate(
        itr, last, std::equal_to<std::iter_value_t<Iter>>{}
    );
}

} // namespace forfun::contains_duplicate

#endif // FORFUN_CONTAINS_DUPLICATE_HPP_
