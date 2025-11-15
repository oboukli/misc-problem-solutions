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
    ConstIter iter,
    Sentinel last,
    Container& subsets
) -> void
{
    if (iter == last) [[unlikely]]
    {
        subsets.emplace_back(subset);
        return;
    }

    std::vector<std::iter_value_t<ConstIter>> current_set{};
    current_set.reserve(subset.size() + 1UZ);

    current_set.assign(subset.cbegin(), subset.cend());

    auto const element{*iter};
    ++iter;

    do_explode_subsets(current_set, iter, last, subsets);

    current_set.emplace_back(element);
    do_explode_subsets(current_set, iter, last, subsets);
}

} // namespace

[[nodiscard]] auto explode_subsets(std::vector<int> const& elements)
    -> std::vector<std::vector<int>>
{
    std::vector<std::vector<int>> subsets{};
    subsets.reserve(1UZ << elements.size());

    std::vector<int> current_subset{};
    current_subset.reserve(0UZ);

    do_explode_subsets(
        current_subset, elements.cbegin(), elements.cend(), subsets
    );

    return subsets;
}

} // namespace forfun::subsets
