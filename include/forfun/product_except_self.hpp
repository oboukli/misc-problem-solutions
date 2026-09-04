// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/product-of-array-except-self/

#ifndef FORFUN_PRODUCT_EXCEPT_SELF_HPP_
#define FORFUN_PRODUCT_EXCEPT_SELF_HPP_

#include <iterator>

#include "common/concepts.hpp"

namespace forfun::product_except_self {

namespace alg1 {

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    typename InIter,
    typename InIterSentinel,
    typename OutIter,
    typename OutIterSentinel>
    requires std::contiguous_iterator<InIter>
    and std::sentinel_for<InIterSentinel, InIter>
    and std::contiguous_iterator<OutIter>
    and std::sentinel_for<OutIterSentinel, OutIter>
    and forfun::common::concepts::
        multipliable_as<std::iter_value_t<InIter>, std::iter_value_t<OutIter>>
constexpr auto product_except_self(
    InIter const first,
    InIterSentinel const last,
    OutIter const products_first,
    OutIterSentinel const products_last
) noexcept -> void
{
    using std::distance;
    using std::next;

    using ValueType = std::iter_value_t<OutIter>;

    static constexpr ValueType const one{1};

    for (
        auto product_iter{products_first}; product_iter != products_last;
        ++product_iter
    )
    {
        *product_iter = one;

        auto in_iter{next(first, distance(products_first, product_iter))};
        auto cnt{first};

        while (++cnt != last)
        {
            ++in_iter;
            if (in_iter == last)
            {
                in_iter = first;
            }
            *product_iter *= static_cast<ValueType>(*in_iter);
        }
    }
}

} // namespace alg1

namespace alg2 {

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    typename InIter,
    typename InIterSentinel,
    typename OutIter,
    typename OutIterSentinel>
    requires std::contiguous_iterator<InIter>
    and std::sentinel_for<InIterSentinel, InIter>
    and std::contiguous_iterator<OutIter>
    and std::sentinel_for<OutIterSentinel, OutIter>
    and forfun::common::concepts::
        multipliable_as<std::iter_value_t<InIter>, std::iter_value_t<OutIter>>
constexpr auto product_except_self(
    InIter const first,
    InIterSentinel const /*unused*/,
    OutIter const products_iter,
    OutIterSentinel const products_last
) noexcept -> void
{
    using std::distance;
    using std::next;

    using ValueType = std::iter_value_t<OutIter>;
    using DiffType = std::iter_difference_t<InIter>;

    static constexpr ValueType const one{1};

    auto const length{products_last - products_iter};
    for (
        auto product_iter{products_iter}; product_iter != products_last;
        ++product_iter
    )
    {
        *product_iter = one;
        auto const idx_prd{distance(products_iter, product_iter)};
        for (auto j{DiffType{1}}; j < length; ++j)
        {
            *product_iter
                *= static_cast<ValueType>(*next(first, (idx_prd + j) % length));
        }
    }
}

} // namespace alg2

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
