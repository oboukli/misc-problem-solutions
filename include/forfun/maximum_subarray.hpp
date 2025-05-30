// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Maximum_subarray_problem

#ifndef FORFUN_MAXIMUM_SUBARRAY_HPP_
#define FORFUN_MAXIMUM_SUBARRAY_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>
#include <limits>
#include <utility>

namespace forfun::maximum_subarray {

template <std::integral T>
using PromotedValueType = decltype(std::declval<T>() + std::declval<T>());

namespace brute_force {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
max_sum(Iter const first, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (first == last) [[unlikely]]
    {
        return T{0};
    }

    T max_sum{std::numeric_limits<T>::min()};
    for (auto iter_i{first}; iter_i != last; ++iter_i)
    {
        T sum{0};
        for (auto iter_j{iter_i}; iter_j != last; ++iter_j)
        {
            sum += *iter_j;
            if (sum > max_sum)
            {
                max_sum = sum;
            }
        }
    }

    return max_sum;
}

} // namespace brute_force

namespace recursive {

namespace detail {

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum_internal(
    Iter iter,
    Sentinel const last,
    PromotedValueType<std::iter_value_t<Iter>> sum
) noexcept -> PromotedValueType<std::iter_value_t<Iter>>
{
    if (iter == last) [[unlikely]]
    {
        return sum;
    }

    PromotedValueType<std::iter_value_t<Iter>> const n{*iter};
    sum = std::max(n, n + sum);

    return std::max(sum, max_sum_internal(++iter, last, sum));
}

} // namespace detail

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum(Iter iter, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (iter == last) [[unlikely]]
    {
        return T{0};
    }

    return detail::max_sum_internal(iter, last, std::min(T{0}, *iter));
}

} // namespace recursive

namespace streaming {

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum(Iter iter, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (iter == last) [[unlikely]]
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
