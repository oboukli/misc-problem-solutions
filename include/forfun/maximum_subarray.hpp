// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Maximum_subarray_problem

#ifndef FORFUN_MAXIMUM_SUBARRAY_HPP_
#define FORFUN_MAXIMUM_SUBARRAY_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>
#include <utility>

namespace forfun::maximum_subarray {

template <std::integral T>
using PromotedValueType = decltype(std::declval<T>() + std::declval<T>());

namespace brute_force {

} // namespace brute_force

namespace streaming {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum(Iter iter, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (iter == last)
    {
        return T{0};
    }

    T sum{std::min(T{0}, *iter)};
    T max_sum{sum};
    for (; iter != last; ++iter)
    {
        T const n{*iter};
        sum = std::max(n, n + sum);

        if (sum > max_sum)
        {
            max_sum = sum;
        }
    }

    return max_sum;
}

} // namespace streaming

} // namespace forfun::maximum_subarray

#endif // FORFUN_MAXIMUM_SUBARRAY_HPP_
