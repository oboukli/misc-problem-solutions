// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/subsets/

#ifndef FORFUN_SUBSETS_HPP_
#define FORFUN_SUBSETS_HPP_

#include <iterator>
#include <vector>

namespace forfun::subsets {

namespace detail {

template <
    std::input_iterator ConstIter,
    std::sentinel_for<ConstIter> Sentinel,
    typename Container>
constexpr auto do_explode_subsets(
    std::vector<std::iter_value_t<ConstIter>> const& subset,
    ConstIter const& first,
    Sentinel const& last,
    Container& subsets
) -> void
{
    if (first == last) [[unlikely]]
    {
        subsets.emplace_back(subset);
        return;
    }

    std::vector<std::iter_value_t<ConstIter>> current_subset{};
    current_subset.reserve(subset.size() + 1UZ);

    current_subset.assign(subset.cbegin(), subset.cend());

    auto const next{std::next(first)};

    do_explode_subsets(current_subset, next, last, subsets);

    current_subset.emplace_back(*first);
    do_explode_subsets(current_subset, next, last, subsets);
}

} // namespace detail

[[nodiscard]] constexpr auto explode_subsets(std::vector<int> const& elements)
    -> std::vector<std::vector<int>>
{
    std::vector<std::vector<int>> subsets{};
    subsets.reserve(1UZ << elements.size());

    std::vector<int> const empty_subset{};

    detail::do_explode_subsets(
        empty_subset, elements.cbegin(), elements.cend(), subsets
    );

    return subsets;
}

} // namespace forfun::subsets

#endif // FORFUN_SUBSETS_HPP_
