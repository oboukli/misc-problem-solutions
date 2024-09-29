// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/top-k-frequent-elements/
/// https://neetcode.io/problems/top-k-elements-in-list

#ifndef FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_
#define FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

namespace forfun::top_k_frequent_elements {

namespace priority_queue_based {

/// Assume input is valid and guarantees having a unique solution.
/// Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const end, std::size_t k) noexcept
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;

    std::size_t const size{static_cast<std::size_t>(end - iter)};

    counts.reserve(size);

    k = std::min(k, size);

    for (; iter != end; ++iter)
    {
        ++counts.try_emplace(*iter, std::size_t{0U}).first->second;
    }

    auto const comparator
        = [](auto const& a, auto const& b) { return a.second < b.second; };
    using T = std::pair<ValType, std::size_t>;
    std::priority_queue<T, std::vector<T>, decltype(comparator)> intermediate(
        comparator
    );
    for (auto const& bucket : counts)
    {
        intermediate.push(bucket);
    }

    std::vector<ValType> result;
    result.reserve(k);
    for (std::size_t i{0U}; i < k; ++i)
    {
        result.push_back(intermediate.top().first);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based

} // namespace forfun::top_k_frequent_elements

#endif // FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_
