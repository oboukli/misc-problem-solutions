// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// - https://leetcode.com/problems/top-k-frequent-elements/
/// - https://neetcode.io/problems/top-k-elements-in-list

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

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter const first, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::size_t const size{static_cast<std::size_t>(last - first)};

    std::vector<std::vector<ValType>> counts(size);

    k = std::min(k, size);

    std::sort(first, last);

    {
        ValType current{*first};
        std::size_t current_count{0UZ};
        auto aux_iter{first};

        ++current_count;
        ++aux_iter;

        for (; aux_iter != last; ++aux_iter)
        {
            if (current != *aux_iter)
            {
                counts[current_count - 1UZ].push_back(current);
                current = *aux_iter;
                current_count = 1UZ;
            }
            else
            {
                ++current_count;
            }
        }
        counts[current_count - 1UZ].push_back(current);
    }

    std::vector<ValType> result;
    result.reserve(k);

    for (auto iter{counts.crbegin()}; k != 0UZ; ++iter)
    {
        assert(iter != counts.crend());

        for (auto j{iter->cbegin()}; (j != iter->cend()) && (k != 0UZ); ++j)
        {
            result.push_back(*j);
            --k;
        }
    }

    return result;
}

} // namespace bucket_sort_based

namespace bucket_sort_based_functional {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter const first, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::vector<std::vector<ValType>> counts(
        static_cast<std::size_t>(last - first)
    );

    std::sort(first, last);

    {
        ValType current{*first};
        std::size_t current_count{0UZ};
        auto aux_iter{first};

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
        do
        {
            if (current == *aux_iter)
            {
                ++current_count;
            }
            else
            {
                counts[current_count - 1UZ].push_back(current);
                current = *aux_iter;
                current_count = 1UZ;
            }

            ++aux_iter;
        } while (aux_iter != last);

        counts[current_count - 1UZ].push_back(current);
    }

    return counts
        | std::views::reverse
        | std::views::join
        | std::views::take(k)
        | std::ranges::to<std::vector>();
}

} // namespace bucket_sort_based_functional

namespace priority_queue_based {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto top_frequent(Iter iter, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    counts.reserve(size);

    k = std::min(k, size);

    for (; iter != last; ++iter)
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
    }

    auto const comparator = [](auto const& a, auto const& b) noexcept -> bool {
        return a.second < b.second;
    };
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
    for (std::size_t i{0UZ}; i < k; ++i)
    {
        result.push_back(intermediate.top().first);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based

namespace priority_queue_based_functional {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto top_frequent(Iter iter, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    counts.reserve(size);

    k = std::min(k, size);

    for (; iter != last; ++iter)
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
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
    for (std::size_t i{0UZ}; i < k; ++i)
    {
        result.push_back(intermediate.top().first);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based_functional

namespace unordered_map_based {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto top_frequent(Iter iter, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    counts.reserve(size);

    k = std::min(k, size);

    for (; iter != last; ++iter)
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
    }

    std::vector<std::pair<ValType, std::size_t>> intermediate;
    intermediate.reserve(size);

    std::copy(counts.cbegin(), counts.cend(), std::back_inserter(intermediate));

    std::sort(
        intermediate.begin(),
        intermediate.end(),
        [](auto const& a, auto const& b) noexcept -> bool {
            return a.second > b.second;
        }
    );

    std::vector<ValType> result;
    result.reserve(k);
    std::transform(
        intermediate.cbegin(),
        intermediate.cbegin()
            + static_cast<decltype(intermediate)::difference_type>(k),
        std::back_inserter(result),
        [](auto const& bucket) noexcept -> ValType { return bucket.first; }
    );

    return result;
}

} // namespace unordered_map_based

namespace unordered_map_based_functional {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValType = std::iter_value_t<Iter>;

    std::unordered_map<ValType, std::size_t> counts;
    counts.reserve(static_cast<std::size_t>(last - iter));

    for (; iter != last; ++iter)
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
    }

    auto intermediate{
        std::ranges::to<std::vector<std::pair<ValType, std::size_t>>>(counts)
    };

    std::ranges::sort(
        intermediate,
        std::ranges::greater{},
        &std::pair<ValType, std::size_t>::second
    );

    return intermediate
        | std::views::take(k)
        | std::views::keys
        | std::ranges::to<std::vector>();
}

} // namespace unordered_map_based_functional

} // namespace forfun::top_k_frequent_elements

#endif // FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_
