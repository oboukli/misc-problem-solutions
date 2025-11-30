// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/subsets/

#ifndef FORFUN_SUBSETS_HPP_
#define FORFUN_SUBSETS_HPP_

#include <cstddef>
#include <iterator>
#include <vector>

namespace forfun::subsets {

namespace iterative {

// (Placeholder)

} // namespace iterative

namespace recursive {

namespace detail {

template <
    typename ConstIter,
    typename Sentinel,
    typename Container,
    typename ElementAllocator>
    requires std::forward_iterator<ConstIter>
    and std::sized_sentinel_for<ConstIter, Sentinel>
constexpr auto do_explode_subsets(
    std::vector<std::iter_value_t<ConstIter>, ElementAllocator> const& subset,
    ConstIter const& first,
    Sentinel const& last,
    Container& subsets,
    ElementAllocator const& element_allocator
) -> void
{
    if (first == last) [[unlikely]]
    {
        subsets.emplace_back(subset);
        return;
    }

    std::vector<std::iter_value_t<ConstIter>, ElementAllocator> current_subset{
        element_allocator
    };
    current_subset.reserve(subset.size() + 1UZ);

    current_subset.assign(subset.cbegin(), subset.cend());

    auto const next{std::next(first)};

    do_explode_subsets(current_subset, next, last, subsets, element_allocator);

    current_subset.emplace_back(*first);
    do_explode_subsets(current_subset, next, last, subsets, element_allocator);
}

} // namespace detail

template <
    typename ConstIter,
    typename Sentinel,
    typename ElementAllocator = std::vector<int>::allocator_type,
    typename SubsetAllocator
    = std::vector<std::vector<int, ElementAllocator>>::allocator_type>
    requires std::contiguous_iterator<ConstIter>
    and std::sized_sentinel_for<ConstIter, Sentinel>
[[nodiscard]] constexpr auto explode_subsets(
    ConstIter const& first,
    Sentinel const& last,
    SubsetAllocator subset_allocator
    = std::vector<std::vector<int>>::allocator_type{},
    ElementAllocator element_allocator = std::vector<int>::allocator_type{}
) -> std::vector<std::vector<int, ElementAllocator>, SubsetAllocator>
{
    std::vector<std::vector<int, ElementAllocator>, SubsetAllocator> subsets{
        subset_allocator
    };
    subsets.reserve(
        1UZ << static_cast<std::size_t>(std::abs(std::distance(first, last)))
    );

    std::vector<int, ElementAllocator> const empty_subset{element_allocator};

    detail::do_explode_subsets(
        empty_subset, first, last, subsets, element_allocator
    );

    return subsets;
}

} // namespace recursive

} // namespace forfun::subsets

#endif // FORFUN_SUBSETS_HPP_
