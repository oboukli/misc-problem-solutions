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

template <std::contiguous_iterator Iter>
[[nodiscard]] constexpr inline bool
contains_duplicate(Iter it, Iter const last) noexcept
{
    for (; it != last; ++it)
    {
        auto const val{*it};

        for (auto it_j{std::next(it)}; it_j != last; ++it_j)
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
