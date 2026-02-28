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

template <typename T>
    requires std::integral<T>
using PromotedValueType = decltype(std::declval<T>() + std::declval<T>());

namespace brute_force {

template <typename Iter, typename Sentinel>
    requires std::forward_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
max_sum(Iter const first, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using std::numeric_limits;

    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (first == last) [[unlikely]]
    {
        return T{};
    }

    T max_sum{numeric_limits<T>::min()};
    for (auto iter_i{first}; iter_i != last; ++iter_i)
    {
        T sum{};
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

template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum_internal(
    Iter iter,
    Sentinel const last,
    PromotedValueType<std::iter_value_t<Iter>> sum
) noexcept -> PromotedValueType<std::iter_value_t<Iter>>
{
    using std::max;

    if (iter == last) [[unlikely]]
    {
        return sum;
    }

    PromotedValueType<std::iter_value_t<Iter>> const num{*iter};
    sum = max(num, num + sum);

    return max(sum, max_sum_internal(++iter, last, sum));
}

} // namespace detail

template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum(Iter iter, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using std::min;

    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (iter == last) [[unlikely]]
    {
        return T{};
    }

    return detail::max_sum_internal(iter, last, min(T{}, *iter));
}

} // namespace recursive

namespace streaming {

template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto max_sum(Iter iter, Sentinel const last) noexcept
    -> PromotedValueType<std::iter_value_t<Iter>>
{
    using std::max;
    using std::min;

    using T = PromotedValueType<std::iter_value_t<Iter>>;

    if (iter == last) [[unlikely]]
    {
        return T{};
    }

    T sum{min(T{}, *iter)};
    T max_sum{sum};
    for (; iter != last; ++iter)
    {
        T const num{*iter};
        sum = max(num, num + sum);

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
