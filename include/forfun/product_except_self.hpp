// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/product-of-array-except-self/

#ifndef FORFUN_PRODUCT_EXCEPT_SELF_HPP_
#define FORFUN_PRODUCT_EXCEPT_SELF_HPP_

#include <iterator>
#include <type_traits>

namespace forfun::product_except_self {

namespace concepts {

template <typename Factor, typename Product>
concept product_computable = requires {
    requires std::is_arithmetic_v<Factor> and std::is_arithmetic_v<Product>
        and requires(Factor f) {
                requires sizeof(decltype(f * f)) <= sizeof(Product);
            };
};

} // namespace concepts

namespace alg1 {

using forfun::product_except_self::concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <std::contiguous_iterator InItr, std::contiguous_iterator OutItr>
// clang-format off
    requires product_computable<
        std::iter_value_t<InItr>,
        std::iter_value_t<OutItr>>
// clang-format on
constexpr auto product_except_self(
    InItr const first,
    InItr const last,
    OutItr const products_first,
    OutItr const products_last) noexcept -> void
{
    for (auto it_prd{products_first}; it_prd != products_last; ++it_prd)
    {
        *it_prd = std::iter_value_t<OutItr>{1};

        auto it_input{first + (it_prd - products_first)};

        auto cnt{first};
        while (++cnt != last)
        {
            ++it_input;
            if (it_input == last)
            {
                it_input = first;
            }
            *it_prd *= *it_input;
        }
    }
}

} // namespace alg1

namespace alg2 {

using forfun::product_except_self::concepts::product_computable;

/// @note Input factors may result in too large a product that overflows the
/// output type.
template <std::contiguous_iterator InItr, std::contiguous_iterator OutItr>
// clang-format off
    requires product_computable<
        std::iter_value_t<InItr>,
        std::iter_value_t<OutItr>>
// clang-format on
constexpr auto product_except_self(
    InItr const first,
    InItr const last,
    OutItr const products_first,
    OutItr const products_last) noexcept -> void
{
    using ValType = std::decay_t<std::iter_value_t<OutItr>>;
    using DiffType = std::iter_difference_t<InItr>;

    if (first == last)
    {
        return;
    }

    auto const length{products_last - products_first};
    for (auto it_prd{products_first}; it_prd != products_last; ++it_prd)
    {
        *it_prd = ValType{1};
        auto const idx_prd{it_prd - products_first};
        for (auto j{DiffType{1}}; j < length; ++j)
        {
            *it_prd *= first[(idx_prd + j) % length];
        }
    }
}

} // namespace alg2

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
