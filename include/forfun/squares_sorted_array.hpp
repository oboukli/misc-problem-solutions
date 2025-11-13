// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/squares-of-a-sorted-array/

#ifndef FORFUN_SQUARES_SORTED_ARRAY_HPP_
#define FORFUN_SQUARES_SORTED_ARRAY_HPP_

#include <concepts>
#include <iterator>

#include "forfun/common/concepts.hpp"

namespace forfun::squares_sorted_array {

namespace detail {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
///
/// @note Multiplication result value may overflow the value type of @p
/// dest_iter.
template <
    std::input_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    std::output_iterator<std::iter_value_t<Iter>> DestIter>
    requires forfun::common::concepts::
        multipliable_as<std::iter_value_t<Iter>, std::iter_value_t<DestIter>>
    constexpr auto
    calc_squares(Iter iter, Sentinel const last, DestIter dest_iter) noexcept
    -> void
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        *dest_iter = (*iter) * (*iter);
        ++iter;
        ++dest_iter;
    } while (iter != last);
}

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
///
/// @note Multiplication result value may overflow the value type of @p
/// dest_iter.
template <
    std::bidirectional_iterator Iter,
    std::output_iterator<std::iter_value_t<Iter>> DestIter>
    requires forfun::common::concepts::
        multipliable_as<std::iter_value_t<Iter>, std::iter_value_t<DestIter>>
    constexpr auto calc_squares_reversed(
        Iter iter, Iter const last, DestIter dest_iter
    ) noexcept -> void
{
    auto r_iter{std::make_reverse_iterator(last)};
    auto r_last{std::make_reverse_iterator(iter)};

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        *dest_iter = (*r_iter) * (*r_iter);
        ++r_iter;
        ++dest_iter;
    } while (r_iter != r_last);
}

} // namespace detail

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
///
/// @note The strategy assumes that @p iter and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
///
/// @note Multiplication result value may overflow the value type of @p
/// dest_iter.
template <
    std::bidirectional_iterator Iter,
    std::bidirectional_iterator DestIter>
    requires std::integral<std::iter_value_t<Iter>>
    and forfun::common::concepts::
        multipliable_as<std::iter_value_t<Iter>, std::iter_value_t<DestIter>>
constexpr auto
squares_sorted(Iter iter, Iter const last, DestIter const dest_iter) noexcept
    -> void
{
    using ValueType = std::iter_value_t<Iter>;

    auto upper{last};
    auto dest_upper{std::next(dest_iter, std::distance(iter, last))};

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        // It is possible to check, at each iteration, whether the remaining
        // sub-array is all non-negative and handover to calc_squares, or all
        // negative and then handover to calc_squares_reversed.

        --dest_upper;
        ValueType const sq1{(*iter) * (*iter)};
        ValueType const sq2{(*std::prev(upper)) * (*std::prev(upper))};
        if (sq1 <= sq2)
        {
            *dest_upper = sq2;
            --upper;
        }
        else
        {
            *dest_upper = sq1;
            ++iter;
        }
    } while (dest_upper != dest_iter);
}

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
///
/// @note The strategy assumes that @p iter and @p last point to a span of
/// positive elements sorted in non-descending order, otherwise the behavior of
/// the strategy is undefined.
///
/// @note Multiplication result value may overflow the value type of @p
/// dest_iter.
template <
    std::input_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::output_iterator<std::iter_value_t<Iter>> DestIter>
    requires std::integral<std::iter_value_t<Iter>>
    and forfun::common::concepts::
        multipliable_as<std::iter_value_t<Iter>, std::iter_value_t<DestIter>>
constexpr auto squares_sorted(
    Iter iter, Sentinel const last, DestIter const dest_iter
) noexcept -> void
{
    detail::calc_squares(iter, last, dest_iter);
}

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements, otherwise the behavior of the strategy is undefined.
///
/// @note The strategy assumes that @p iter and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
///
/// @note Multiplication result value may overflow the value type of @p
/// dest_iter.
template <
    std::bidirectional_iterator Iter,
    std::bidirectional_iterator DestIter>
    requires std::integral<std::iter_value_t<Iter>>
    and forfun::common::concepts::
        multipliable_as<std::iter_value_t<Iter>, std::iter_value_t<DestIter>>
constexpr auto squares_sorted_special(
    Iter const iter, Iter const last, DestIter const dest_iter
) noexcept -> void
{
    using ValueType = std::iter_value_t<Iter>;

    // Can assume all values are non-negative.
    if (*iter >= ValueType{})
    {
        detail::calc_squares(iter, last, dest_iter);

        return;
    }

    auto upper{std::prev(last)};

    // Can assume all values are negative.
    if (*upper < ValueType{})
    {
        detail::calc_squares_reversed(iter, last, dest_iter);

        return;
    }

    squares_sorted(iter, last, dest_iter);
}

} // namespace forfun::squares_sorted_array

#endif // FORFUN_SQUARES_SORTED_ARRAY_HPP_
