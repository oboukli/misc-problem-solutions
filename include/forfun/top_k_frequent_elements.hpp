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
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <iterator>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

namespace forfun::top_k_frequent_elements {

namespace bucket_sort_based {

/// Assume input is valid and guarantees having a unique solution.
/// Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter const first, Sentinel const end, std::size_t k) noexcept
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    if (first == end)
    {
        return {};
    }

    std::sort(first, end);

    std::size_t const size{static_cast<std::size_t>(end - first)};

    std::vector<std::vector<ValType>> counts(size);

    k = std::min(k, size);

    ValType current{*first};
    std::size_t current_count{0U};
    std::size_t counts_size{1U};
    for (auto aux_iter{first}; aux_iter != end; ++aux_iter)
    {
        if (current == *aux_iter)
        {
            ++current_count;
        }
        else
        {
            if (counts[current_count - 1U].empty())
            {
                ++counts_size;
            }
            counts[current_count - 1U].push_back(current);
            current = *aux_iter;
            current_count = 1U;
        }
    }
    counts[current_count - 1U].push_back(current);
    ++counts_size;

    std::vector<ValType> result;
    result.reserve(k);

    for (auto iter{counts.crbegin()}; k != std::size_t{0U}; ++iter)
    {
        assert(iter != counts.crend());
        auto const iter_cend{iter->cend()};
        // clang-format off
        for (auto j{iter->cbegin()}; j != iter_cend && k != std::size_t{0U};
            ++j)
        // clang-format on
        {
            result.push_back(*j);
            --k;
        }
    }

    return result;
}

} // namespace bucket_sort_based

namespace bucket_sort_based_functional {

/// Assume input is valid and guarantees having a unique solution.
/// Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter const first, Sentinel const end, std::size_t k) noexcept
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    if (first == end)
    {
        return {};
    }

    std::sort(first, end);

    std::vector<std::vector<ValType>> counts(
        static_cast<std::size_t>(end - first)
    );

    ValType current{*first};
    std::size_t current_count{0U};
    std::size_t counts_size{1U};
    for (auto aux_iter{first}; aux_iter != end; ++aux_iter)
    {
        if (current == *aux_iter)
        {
            ++current_count;
        }
        else
        {
            if (counts[current_count - 1U].empty())
            {
                ++counts_size;
            }
            counts[current_count - 1U].push_back(current);
            current = *aux_iter;
            current_count = 1U;
        }
    }
    counts[current_count - 1U].push_back(current);
    ++counts_size;

    return counts
        | std::views::reverse
        | std::views::join
        | std::views::take(k)
        | std::ranges::to<std::vector>();
}

} // namespace bucket_sort_based_functional

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

namespace priority_queue_based_functional {

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

    auto const comparator = [](auto const& a, auto const& b) noexcept -> bool {
        return a.second < b.second;
    };
    using T = std::pair<ValType, std::size_t>;

    auto intermediate{std::ranges::to<
        std::priority_queue<T, std::vector<T>, decltype(comparator)>>(
        counts, comparator
    )};

    std::vector<ValType> result;
    result.reserve(k);
    for (std::size_t i{0U}; i < k; ++i)
    {
        result.push_back(intermediate.top().first);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based_functional

namespace unordered_map_based {

/// Assume input is valid and guarantees having a unique solution.
/// Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
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

    std::vector<std::pair<ValType, std::size_t>> intermediate;
    intermediate.reserve(size);

    std::copy(counts.cbegin(), counts.cend(), std::back_inserter(intermediate));

    std::sort(
        intermediate.begin(),
        intermediate.end(),
        [](auto const& a, auto const& b) { return a.second > b.second; }
    );

    std::vector<ValType> result;
    result.reserve(k);
    std::transform(
        intermediate.cbegin(),
        intermediate.cbegin()
            + static_cast<decltype(intermediate)::difference_type>(k),
        std::back_inserter(result),
        [](auto const& bucket) { return bucket.first; }
    );

    return result;
}

} // namespace unordered_map_based

namespace unordered_map_based_functional {

/// Assume input is valid and guarantees having a unique solution.
/// Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const end, std::size_t const k) noexcept
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;
    counts.reserve(static_cast<std::size_t>(end - iter));

    for (; iter != end; ++iter)
    {
        ++counts.try_emplace(*iter, std::size_t{0U}).first->second;
    }

    auto intermediate{
        std::ranges::to<std::vector<std::pair<ValType, std::size_t>>>(counts)
    };

    std::ranges::sort(intermediate, [](auto&& a, auto&& b) noexcept {
        return std::ranges::greater{}(a.second, b.second);
    });

    return intermediate
        | std::views::take(k)
        | std::views::keys
        | std::ranges::to<std::vector>();
}

} // namespace unordered_map_based_functional

} // namespace forfun::top_k_frequent_elements

#endif // FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_
