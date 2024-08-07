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
#include <concepts>
#include <iterator>

namespace forfun::sub_array_sums {

template <typename Nums, typename Sums>
// clang-format off
    requires std::contiguous_iterator<typename Nums::iterator>
        and std::output_iterator<
            typename Sums::iterator, typename Nums::value_type>
        and std::same_as<typename Nums::size_type, typename Sums::size_type>
        and requires(Nums::value_type num, Sums::value_type sum) {
            sum += num;
            sum -= num;
        }
// clang-format on
constexpr auto sum_each(
    Nums const& nums, Sums& sums, typename Nums::size_type const sub_size
) noexcept -> void
{
    using SizeType = Sums::size_type;
    using ValueType = Sums::value_type;
    using DiffType = Nums::difference_type;

    auto const sums_size{sums.size()};

    if (sums_size == SizeType{0})
    {
        return;
    }

    ValueType sub_sum{};
    auto nums_it{nums.cbegin()};
    auto const nums_size{nums.size()};

    // Calculate result for the first output element.
    auto const nums_bound{std::min(sub_size, nums_size)};
    for (SizeType i{}; i < nums_bound; ++i)
    {
        sub_sum += *nums_it;
        ++nums_it;
    }
    auto sums_it{sums.begin()};
    *sums_it = sub_sum;

    // Stop if no more than one sum element is possible.
    if (sub_size > nums_size)
    {
        return;
    }

    // Slide the window and update sum.
    nums_it = nums.cbegin();
    auto slider_last{nums_it + static_cast<DiffType>(sub_size)};
    auto const sums_bound{
        std::min(sums_size, (nums_size - sub_size) + SizeType{1})
    };
    for (SizeType i{1}; i < sums_bound; ++i)
    {
        // Subtract the element before the sliding window.
        sub_sum -= *nums_it;

        // Add the element at the end of the sliding window.
        sub_sum += *slider_last;

        ++nums_it;
        ++slider_last;

        ++sums_it;
        *sums_it = sub_sum;
    }
}

} // namespace forfun::sub_array_sums

#endif // FORFUN_SUB_ARRAY_SUMS_HPP_
