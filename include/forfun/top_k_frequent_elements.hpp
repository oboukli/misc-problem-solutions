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

namespace detail {

template <typename T>
struct value_count_pair final {
    T value_;

    std::size_t count_;
};

} // namespace detail

namespace bucket_sort_based {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto top_frequent(Iter iter, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValueType = std::iter_value_t<Iter>;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    std::unordered_map<ValueType, std::size_t> counts{};
    counts.reserve(size);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    std::vector<std::vector<ValueType>> buckets(size + 1UZ);

    for (auto&& [value, count] : counts)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
        buckets[count].emplace_back(value);
    }

    std::vector<ValueType> result{};
    result.reserve(k);

    for (auto iter_i{std::crbegin(buckets)}; k != 0UZ; ++iter_i)
    {
        auto const last_j{std::cend(*iter_i)};
        for (
            auto iter_j{std::cbegin(*iter_i)}; (iter_j != last_j) && (k != 0UZ);
            ++iter_j
        )
        {
            result.emplace_back(*iter_j);
            --k;
        }
    }

    return result;
}

} // namespace bucket_sort_based

namespace bucket_sort_based_functional {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using ValueType = std::iter_value_t<Iter>;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    std::unordered_map<ValueType, std::size_t> counts(size);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    std::vector<std::vector<ValueType>> buckets(size + 1UZ);

    for (auto&& [value, count] : counts)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
        buckets[count].emplace_back(std::forward<decltype(value)>(value));
    }

    using DiffType = std::ranges::range_difference_t<decltype(buckets)>;

    return buckets
        | std::views::reverse
        | std::views::join
        | std::views::take(static_cast<DiffType>(k))
        | std::views::as_rvalue
        | std::ranges::to<std::vector>();
}

} // namespace bucket_sort_based_functional

namespace max_heap_based {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::less;

    using ValueType = std::iter_value_t<Iter>;
    using CountPair = detail::value_count_pair<ValueType>;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    std::unordered_map<ValueType, size_t> counts{};
    counts.reserve(size);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    auto const comparator
        = [](auto const& a, auto const& b) constexpr noexcept -> bool {
        return less<std::size_t>{}(a.count_, b.count_);
    };

    std::vector<CountPair> counts_heap{};
    counts_heap.reserve(counts.size());
    counts_heap.emplace_back(counts.cbegin()->first, counts.cbegin()->second);

    for (auto&& count : counts | std::views::drop(1))
    {
        counts_heap.emplace_back(count.first, count.second);
        std::push_heap(counts_heap.begin(), counts_heap.end(), comparator);
    }

    std::vector<std::iter_value_t<Iter>> result{};
    result.reserve(k);

    for (std::size_t i{}; i < k; ++i)
    {
        std::pop_heap(counts_heap.begin(), counts_heap.end(), comparator);
        result.push_back(counts_heap.back().value_);
        counts_heap.pop_back();
    }

    return result;
}

} // namespace max_heap_based

namespace priority_queue_based {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::less;

    using ValueType = std::iter_value_t<Iter>;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    std::unordered_map<ValueType, std::size_t> counts;
    counts.reserve(size);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    auto const comparator
        = [](auto const& a, auto const& b) constexpr noexcept -> bool {
        return less<std::size_t>{}(a.second, b.second);
    };

    using CountPair = std::pair<ValueType, std::size_t>;

    std::priority_queue<CountPair, std::vector<CountPair>, decltype(comparator)>
        intermediate(comparator);

    for (auto const& buckets : counts)
    {
        intermediate.push(buckets);
    }

    std::vector<ValueType> result;
    result.reserve(k);

    for (std::size_t i{}; i < k; ++i)
    {
        result.push_back(intermediate.top().first);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based

namespace priority_queue_based_functional {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto top_frequent(Iter iter, Sentinel const last, std::size_t k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::less;

    using ValueType = std::iter_value_t<Iter>;
    using CountPair = detail::value_count_pair<ValueType>;

    std::size_t const size{static_cast<std::size_t>(last - iter)};

    std::unordered_map<ValueType, std::size_t> counts;
    counts.reserve(size);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    auto const comparator
        = [](auto const& a, auto const& b) constexpr noexcept -> bool {
        return less<std::size_t>{}(a.count_, b.count_);
    };

    auto intermediate{
        counts
        | std::views::transform(
            [](std::pair<ValueType const, std::size_t>& pair)
                -> detail::value_count_pair<ValueType> {
                return detail::value_count_pair<ValueType>{
                    pair.first, pair.second
                };
            }
        )
        | std::ranges::to<std::priority_queue<
            CountPair,
            std::vector<CountPair>,
            decltype(comparator)>>(comparator)
    };

    std::vector<ValueType> result;
    result.reserve(k);

    for (std::size_t i{}; i < k; ++i)
    {
        result.push_back(intermediate.top().value_);
        intermediate.pop();
    }

    return result;
}

} // namespace priority_queue_based_functional

namespace sort_based {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::greater;

    using ValueType = std::iter_value_t<Iter>;
    using CountPair = std::pair<ValueType, std::size_t>;

    std::unordered_map<ValueType, std::size_t> counts;
    counts.reserve(static_cast<std::size_t>(last - iter));

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    std::vector<CountPair> intermediate;
    intermediate.reserve(counts.size());

    std::copy(cbegin(counts), cend(counts), std::back_inserter(intermediate));

    std::ranges::sort(
        intermediate, greater<std::size_t>{}, &CountPair::second

    );

    std::vector<ValueType> result{};
    result.reserve(k);

    using DiffType = std::ranges::range_difference_t<decltype(intermediate)>;

    std::transform(
        std::cbegin(intermediate),
        std::next(std::cbegin(intermediate), static_cast<DiffType>(k)),
        std::back_inserter(result),
        [](auto const& buckets) constexpr noexcept -> ValueType {
            return buckets.first;
        }
    );

    return result;
}

} // namespace sort_based

namespace sort_based_functional_1 {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::ranges::greater;

    using ValueType = std::iter_value_t<Iter>;

    std::unordered_map<ValueType, std::size_t> counts;
    counts.reserve(static_cast<std::size_t>(last - iter));

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    auto intermediate{
        std::ranges::to<std::vector<std::pair<ValueType, std::size_t>>>(counts)
    };

    std::ranges::sort(
        intermediate, greater{}, &std::pair<ValueType, std::size_t>::second
    );

    using DiffType = std::ranges::range_difference_t<decltype(intermediate)>;

    return intermediate
        | std::views::take(static_cast<DiffType>(k))
        | std::views::keys
        | std::ranges::to<std::vector>();
}

} // namespace sort_based_functional_1

namespace sort_based_functional_2 {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
/// @note The strategy assumes that the input is valid and has a unique
/// solution. Invalid input may result in undefined behavior.
template <typename Iter, typename Sentinel>
    requires std::input_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
top_frequent(Iter iter, Sentinel const last, std::size_t const k)
    -> std::vector<std::iter_value_t<Iter>>
{
    using std::ranges::greater;

    using ValueType = std::iter_value_t<Iter>;

    std::unordered_map<ValueType, std::size_t> counts;
    counts.reserve(static_cast<std::size_t>(last - iter));

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        ++counts.try_emplace(*iter, 0UZ).first->second;
        ++iter;
    } while (iter != last);

    auto intermediate{
        counts
        | std::views::transform(
            [](std::pair<ValueType const, std::size_t>& pair)
                -> detail::value_count_pair<ValueType> {
                return detail::value_count_pair<ValueType>{
                    pair.first, pair.second
                };
            }
        )
        | std::ranges::to<std::vector<detail::value_count_pair<ValueType>>>()
    };

    std::ranges::sort(
        intermediate, greater{}, &detail::value_count_pair<ValueType>::count_
    );

    using DiffType = std::ranges::range_difference_t<decltype(intermediate)>;

    // clang-format off
    return intermediate
        | std::views::take(static_cast<DiffType>(k))
        | std::views::transform(
            [](
                detail::value_count_pair<ValueType>& count_pair
            ) -> ValueType& { return count_pair.value_; }
        )
        | std::ranges::to<std::vector<ValueType>>();
    // clang-format on
}

} // namespace sort_based_functional_2

} // namespace forfun::top_k_frequent_elements

#endif // FORFUN_TOP_K_FREQUENT_ELEMENTS_HPP_
