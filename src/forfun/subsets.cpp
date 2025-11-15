// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/subsets.hpp"

#include <iterator>
#include <vector>

namespace forfun::subsets {

namespace {

template <
    std::input_iterator ConstIter,
    std::sentinel_for<ConstIter> Sentinel,
    typename Container>
auto do_explode_subsets(
    std::vector<std::iter_value_t<ConstIter>>& subset,
    ConstIter first,
    Sentinel last,
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

    auto const element{*first};
    ++first;

    do_explode_subsets(current_subset, first, last, subsets);

    current_subset.emplace_back(element);
    do_explode_subsets(current_subset, first, last, subsets);
}

} // namespace

[[nodiscard]] auto explode_subsets(std::vector<int> const& elements)
    -> std::vector<std::vector<int>>
{
    std::vector<std::vector<int>> subsets{};
    subsets.reserve(1UZ << elements.size());

    std::vector<int> empty_subset{};
    empty_subset.reserve(0UZ);

    do_explode_subsets(
        empty_subset, elements.cbegin(), elements.cend(), subsets
    );

    return subsets;
}

} // namespace forfun::subsets
