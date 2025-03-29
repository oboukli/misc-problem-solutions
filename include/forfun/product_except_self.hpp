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

using forfun::product_except_self::concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    std::contiguous_iterator InItr,
    std::sentinel_for<InItr> InItrSentinel,
    std::contiguous_iterator OutItr,
    std::sentinel_for<OutItr> OutItrSentinel>
    requires product_computable<
        std::iter_value_t<InItr>,
        std::iter_value_t<OutItr>>
constexpr auto product_except_self(
    InItr const first,
    InItrSentinel const last,
    OutItr const products_first,
    OutItrSentinel const products_last
) noexcept -> void
{
    using ValType = std::iter_value_t<OutItr>;

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

using forfun::product_except_self::concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <
    std::contiguous_iterator InItr,
    std::sentinel_for<InItr> InItrSentinel,
    std::contiguous_iterator OutItr,
    std::sized_sentinel_for<OutItr> OutItrSentinel>
    requires product_computable<
        std::iter_value_t<InItr>,
        std::iter_value_t<OutItr>>
constexpr auto product_except_self(
    InItr const first,
    InItrSentinel const last,
    OutItr const products_itr,
    OutItrSentinel const products_last
) noexcept -> void
{
    using ValType = std::iter_value_t<OutItr>;
    using DiffType = std::iter_difference_t<InItr>;

    if (first == last) [[unlikely]]
    {
        return;
    }

    auto const length{products_last - products_itr};
    for (auto it_prd{products_itr}; it_prd != products_last; ++it_prd)
    {
        *it_prd = ValType{1};
        auto const idx_prd{it_prd - products_itr};
        for (auto j{DiffType{1}}; j < length; ++j)
        {
            *it_prd *= static_cast<ValType>(first[(idx_prd + j) % length]);
        }
    }
}

} // namespace alg2

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
