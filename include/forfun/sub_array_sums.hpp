// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// Given an array, find all subarrays of length K
/// Sum of all subarrays of size K
/// https://www.youtube.com/watch?v=GcW4mgmgSbw

#ifndef FORFUN_SUB_ARRAY_SUMS_HPP_
#define FORFUN_SUB_ARRAY_SUMS_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sub_array_sums {

template <typename T, typename TSum>
// clang-format off
    requires std::contiguous_iterator<typename T::iterator>
        and std::contiguous_iterator<typename TSum::iterator>
// clang-format on
auto sum_each(
    T const& numbers,
    TSum& sums,
    typename T::size_type const sub_size) noexcept -> void
{
    using S = T::size_type;
    using V = T::value_type;

    auto const nums_size{numbers.size()};
    V sub_sum{};

    // Result container element count.
    auto const sums_size{sums.size()};

    if (sums_size == S{0})
    {
        return;
    }

    // Calculate result for the first output element.
    auto const nums_bound{std::min(sub_size, nums_size)};
    for (S i{}; i < nums_bound; ++i)
    {
        sub_sum += numbers[i];
    }
    sums[S{0}] = sub_sum;

    if (sub_size == S{0} || sub_size > nums_size)
    {
        return;
    }

    // Calculate the remaining result(s).
    auto const sums_bound{
        std::min(sums_size, numbers.size() - sub_size + S{1})};
    auto const ss{sub_size - S{1}};
    for (S i{1}; i < sums_bound; ++i)
    {
        sub_sum -= numbers[i - S{1}];
        sub_sum += numbers[i + ss];

        sums[i] = sub_sum;
    }
}

} // namespace forfun::sub_array_sums

#endif // FORFUN_SUB_ARRAY_SUMS_HPP_
