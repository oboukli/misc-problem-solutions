// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/contains-duplicate/

#ifndef FORFUN_CONTAINS_DUPLICATE_HPP_
#define FORFUN_CONTAINS_DUPLICATE_HPP_

#include <iterator>

namespace forfun::contains_duplicate {

template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
[[nodiscard]] constexpr auto
contains_duplicate(Iter itr, Sentinel const last) noexcept -> bool
{
    for (; itr != last; ++itr)
    {
        auto const val{*itr};
        auto it_j{itr};
        for (++it_j; it_j != last; ++it_j)
        {
            if ((*it_j) == val)
            {
                return true;
            }
        }
    }

    return false;
}

} // namespace forfun::contains_duplicate

#endif // FORFUN_CONTAINS_DUPLICATE_HPP_
