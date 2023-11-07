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

template <typename RandomIt>
    requires std::forward_iterator<RandomIt>
[[nodiscard]] constexpr inline bool
contains_duplicate(RandomIt const first, RandomIt const end) noexcept
{
    for (auto it_i{first}; it_i != end; ++it_i)
    {
        auto const t{*it_i};

        for (auto it_j{it_i + 1}; it_j != end; ++it_j)
        {
            if ((*it_j) == t)
            {
                return true;
            }
        }
    }

    return false;
}

} // namespace forfun::contains_duplicate

#endif // FORFUN_CONTAINS_DUPLICATE_HPP_
