// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/product-of-array-except-self/

#ifndef FORFUN_PRODUCT_EXCEPT_SELF_HPP_
#define FORFUN_PRODUCT_EXCEPT_SELF_HPP_

#include <concepts>
#include <iterator>

namespace forfun::product_except_self {

namespace concepts {

template <typename Factor, typename Product>
concept product_computable = requires(Factor f, Product p) {
    { f * f } -> std::convertible_to<Product>;
};

} // namespace concepts

namespace alg1 {

using concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    std::contiguous_iterator InIter,
    std::sentinel_for<InIter> InIterSentinel,
    std::contiguous_iterator OutIter,
    std::sentinel_for<OutIter> OutIterSentinel>
    requires product_computable<
        std::iter_value_t<InIter>,
        std::iter_value_t<OutIter>>
constexpr auto product_except_self(
    InIter const first,
    InIterSentinel const last,
    OutIter const products_first,
    OutIterSentinel const products_last
) noexcept -> void
{
    using ValType = std::iter_value_t<OutIter>;

    for (auto it_prd{products_first}; it_prd != products_last; ++it_prd)
    {
        *it_prd = ValType{1};

        auto it_input{first + (it_prd - products_first)};

        auto cnt{first};
        while (++cnt != last)
        {
            ++it_input;
            if (it_input == last)
            {
                it_input = first;
            }
            *it_prd *= static_cast<ValType>(*it_input);
        }
    }
}

} // namespace alg1

namespace alg2 {

using concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    std::contiguous_iterator InIter,
    std::sentinel_for<InIter> InIterSentinel,
    std::contiguous_iterator OutIter,
    std::sized_sentinel_for<OutIter> OutIterSentinel>
    requires product_computable<
        std::iter_value_t<InIter>,
        std::iter_value_t<OutIter>>
constexpr auto product_except_self(
    InIter const first,
    InIterSentinel const last,
    OutIter const products_iter,
    OutIterSentinel const products_last
) noexcept -> void
{
    using ValType = std::iter_value_t<OutIter>;
    using DiffType = std::iter_difference_t<InIter>;

    if (first == last) [[unlikely]]
    {
        return;
    }

    auto const length{products_last - products_iter};
    for (auto it_prd{products_iter}; it_prd != products_last; ++it_prd)
    {
        *it_prd = ValType{1};
        auto const idx_prd{it_prd - products_iter};
        for (auto j{DiffType{1}}; j < length; ++j)
        {
            *it_prd *= static_cast<ValType>(first[(idx_prd + j) % length]);
        }
    }
}

} // namespace alg2

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
