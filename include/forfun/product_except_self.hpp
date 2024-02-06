// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/product-of-array-except-self/

#ifndef FORFUN_PRODUCT_EXCEPT_SELF_HPP_
#define FORFUN_PRODUCT_EXCEPT_SELF_HPP_

#include <concepts>
#include <iterator>
#include <type_traits>

namespace forfun::product_except_self {

namespace alg1 {

template <
    typename InItr,
    typename OutItr,
    typename T
    = std::decay_t<typename std::iterator_traits<OutItr>::value_type>>
    requires std::forward_iterator<InItr> && std::forward_iterator<OutItr>
    && (std::integral<T> || std::floating_point<T>)
constexpr inline void product_except_self(
    InItr const first,
    InItr const last,
    OutItr const products_first,
    OutItr const products_last) noexcept
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

template <
    typename InItr,
    typename OutItr,
    typename T
    = std::decay_t<typename std::iterator_traits<OutItr>::value_type>>
    requires std::forward_iterator<InItr> && std::forward_iterator<OutItr>
    && (std::integral<T> || std::floating_point<T>)
constexpr inline void product_except_self(
    InItr const first,
    InItr const last,
    OutItr const products_first,
    OutItr const products_last) noexcept
{
    using Diff = std::iterator_traits<InItr>::difference_type;

    if (first == last)
    {
        return;
    }

    auto const length{products_last - products_first};
    for (auto it_prd{products_first}; it_prd != products_last; ++it_prd)
    {
        *it_prd = T{1};
        auto const idx_prd{it_prd - products_first};
        for (auto j{Diff{1}}; j < length; ++j)
        {
            *it_prd *= first[(idx_prd + j) % length];
        }
    }
}

} // namespace alg2

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
