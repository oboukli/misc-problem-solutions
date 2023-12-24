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

namespace base {

template <
    typename RandomIt,
    typename OutRandomIt,
    typename T
    = std::decay_t<typename std::iterator_traits<OutRandomIt>::value_type>>
    requires std::forward_iterator<RandomIt>
    && std::forward_iterator<OutRandomIt>
    && (std::integral<T> || std::floating_point<T>)
constexpr inline void product_except_self(
    RandomIt const first,
    RandomIt const end,
    OutRandomIt const products_first,
    OutRandomIt const products_end) noexcept
{
    for (auto it_prd{products_first}; it_prd != products_end; ++it_prd)
    {
        *it_prd = T{1};

        auto it_input{first + (it_prd - products_first)};
        auto cnt{first};
        while (++cnt != end)
        {
            ++it_input;
            if (it_input == end)
            {
                it_input = first;
            }
            *it_prd *= *it_input;
        }
    }
}

} // namespace base

namespace fast {

template <
    typename RandomIt,
    typename OutRandomIt,
    typename T
    = std::decay_t<typename std::iterator_traits<OutRandomIt>::value_type>,
    typename Diff = std::iterator_traits<RandomIt>::difference_type>
    requires std::forward_iterator<RandomIt>
    && std::forward_iterator<OutRandomIt>
    && (std::integral<T> || std::floating_point<T>)
constexpr inline void product_except_self(
    RandomIt const first,
    RandomIt const end,
    OutRandomIt const products_first,
    OutRandomIt const products_end) noexcept
{
    if (first == end)
    {
        return;
    }

    auto const length{products_end - products_first};
    for (auto it_prd{products_first}; it_prd != products_end; ++it_prd)
    {
        *it_prd = T{1};

        auto const idx_prd{it_prd - products_first};

        for (Diff j{1}; j < length; ++j)
        {
            *it_prd *= first[(idx_prd + j) % length];
        }
    }
}

} // namespace fast

} // namespace forfun::product_except_self

#endif // FORFUN_PRODUCT_EXCEPT_SELF_HPP_
