// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Binary_search_algorithm

#ifndef FORFUN_SEARCH_BINARY_SEARCH_HPP_
#define FORFUN_SEARCH_BINARY_SEARCH_HPP_

#include <concepts>
#include <functional>
#include <iterator>

namespace forfun::search::binary_search {

namespace iterative {

/// @note The strategy assumes that @p lhs and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
    requires std::forward_iterator<Sentinel>
[[nodiscard]] constexpr auto
find(Iter lhs, Sentinel const last, Target const target) noexcept -> Iter
{
    using std::advance;
    using std::distance;
    using std::greater;
    using std::less;
    using std::next;

    using DiffType = std::iter_difference_t<Iter>;

    static constexpr DiffType const two{2};

    for (Iter rhs{last}; lhs != rhs;)
    {
        auto const num_elements{distance(lhs, rhs)};
        Iter mid{next(lhs, num_elements / two)};
        if (less{}(target, *mid))
        {
            rhs = mid;

            continue;
        }

        if (greater{}(target, *mid))
        {
            advance(lhs, (num_elements / two) + (num_elements % two));

            continue;
        }

        return mid;
    }

    return last;
}

} // namespace iterative

namespace iterative_approach_b {

/// @note The strategy assumes that @p lhs and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
    requires std::forward_iterator<Sentinel>
[[nodiscard]] constexpr auto
find(Iter lhs, Sentinel const last, Target const target) noexcept -> Iter
{
    using std::advance;
    using std::distance;
    using std::greater;
    using std::less;
    using std::next;

    using DiffType = std::iter_difference_t<Iter>;

    static constexpr DiffType const two{2};

    auto num_elements{distance(lhs, last)};

    for (Iter rhs{last}; lhs != rhs;)
    {
        DiffType const quotient{num_elements / two};
        DiffType const remainder{num_elements % two};
        Iter mid{next(lhs, quotient)};
        if (less{}(target, *mid))
        {
            rhs = mid;
            num_elements = quotient + remainder;

            continue;
        }

        if (greater{}(target, *mid))
        {
            advance(lhs, quotient + remainder);
            num_elements = quotient;

            continue;
        }

        return mid;
    }

    return last;
}

} // namespace iterative_approach_b

namespace recursive {

namespace detail {

template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
[[nodiscard]] constexpr auto
do_find(Iter first, Sentinel last, Target const target) noexcept -> Iter
{
    using DiffType = std::iter_difference_t<Iter>;

    using std::distance;
    using std::greater;
    using std::less;
    using std::next;

    static constexpr DiffType const one{1};
    static constexpr DiffType const two{2};

    auto const num_elements{distance(first, last)};
    if (less{}(num_elements, one))
    {
        return last;
    }

    Iter mid{next(first, num_elements / two)};
    if (less{}(target, *mid))
    {
        return do_find(first, mid, target);
    }

    if (greater{}(target, *mid))
    {
        return do_find(next(mid), last, target);
    }

    return mid;
}

} // namespace detail

/// @note The strategy assumes that @p first and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
[[nodiscard]] constexpr auto
find(Iter first, Sentinel last, Target const target) noexcept -> Iter
{
    using std::equal_to;

    if (Iter iter{detail::do_find(first, last, target)};
        (iter != last) && equal_to{}(*iter, target))
    {
        return iter;
    }

    return last;
}

} // namespace recursive

} // namespace forfun::search::binary_search

#endif // FORFUN_SEARCH_BINARY_SEARCH_HPP_
