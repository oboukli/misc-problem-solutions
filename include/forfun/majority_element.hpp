// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm

#ifndef FORFUN_MAJORITY_ELEMENT_HPP_
#define FORFUN_MAJORITY_ELEMENT_HPP_

#include <iterator>

namespace forfun::majority_element {

template <typename Elements>
    requires std::forward_iterator<typename Elements::iterator>
[[nodiscard]] constexpr auto
majority_element(Elements const& elements) noexcept -> Elements::const_iterator
{
    using ElementType = Elements::value_type;
    using SizeType = Elements::size_type;
    using Itr = Elements::const_iterator;

    SizeType const size{elements.size()};
    Itr const cend{elements.cend()};

    if (size < SizeType{3})
    {
        return cend;
    }

    SizeType threshold{(size / SizeType{2}) + SizeType{1}};
    SizeType count{0};
    ElementType majority_elm{}; // Unecessary default initialization.
    Itr majority_itr{}; // Unecessary default initialization.

    for (Itr itr{elements.cbegin()}; itr != cend; ++itr)
    {
        if (count == SizeType{0})
        {
            majority_elm = *itr;
            majority_itr = itr;
        }

        if (*itr == majority_elm)
        {
            ++count;
            if (count == threshold)
            {
                return majority_itr;
            }
        }
        else
        {
            --count;
        }
    }

    for (auto itr{elements.cbegin()}; itr != cend; ++itr)
    {
        if (*itr == majority_elm)
        {
            --threshold;
        }

        if (threshold == 0)
        {
            return majority_itr;
        }
    }

    return cend;
}

} // namespace forfun::majority_element

#endif // FORFUN_MAJORITY_ELEMENT_HPP_
