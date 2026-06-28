// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/daily-temperatures/

#ifndef FORFUN_DAILY_TEMPERATURES_HPP_
#define FORFUN_DAILY_TEMPERATURES_HPP_

#include <cassert>
#include <concepts>
#include <functional>
#include <iterator>

namespace forfun::daily_temperatures {

/// @note The range defined by @p first and @p last must not be empty.
/// @note The range represented by @p dest_first must be zero initialized.
/// @note The range represented by @p dest_first must not be smaller than the
/// range defined by @p first and @p last.
/// @note The range represented by @p scratch_first must not be smaller than the
/// range defined by @p first and @p last.
template <
    typename Iter,
    typename Sentinel,
    typename OutIter,
    typename ScratchIter>
    requires std::forward_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::forward_iterator<OutIter>
    and std::bidirectional_iterator<ScratchIter>
    and std::
        same_as<std::iter_difference_t<Iter>, std::iter_difference_t<OutIter>>
    and std::
        same_as<std::iter_difference_t<Iter>, std::iter_value_t<ScratchIter>>
constexpr auto daily_temperatures(
    Iter const first,
    Sentinel const last,
    OutIter const dest_first,
    ScratchIter const scratch_first
) noexcept -> void
{
    using DestValueType = std::iter_value_t<OutIter>;
    using DiffType = std::iter_difference_t<Iter>;
    using ValueType = std::iter_value_t<Iter>;

    using std::distance;
    using std::greater;
    using std::next;
    using std::prev;

    assert(first != last);

    auto const size{distance(first, last)};
    assert(size > DiffType{});

    auto top_iter{scratch_first};
    *top_iter = DiffType{};
    ++top_iter;

    for (DiffType i{1}; i < size; ++i)
    {
        while (
            (top_iter != scratch_first)
            && greater<ValueType>{}(
                *next(first, i), *next(first, *prev(top_iter))
            )
        )
        {
            auto const top_val{*prev(top_iter)};
            *next(dest_first, top_val)
                = static_cast<DestValueType>(i - top_val);
            --top_iter;
        }

        *top_iter = i;
        ++top_iter;
    }
}

} // namespace forfun::daily_temperatures

#endif // FORFUN_DAILY_TEMPERATURES_HPP_
