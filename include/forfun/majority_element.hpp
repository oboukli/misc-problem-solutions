// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm

#ifndef FORFUN_MAJORITY_ELEMENT_HPP_
#define FORFUN_MAJORITY_ELEMENT_HPP_

#include <iterator>

namespace forfun::majority_element {

template <typename Elements>
    requires std::forward_iterator<typename Elements::iterator>
[[nodiscard]] constexpr auto majority_element(Elements const& elements) noexcept
    -> Elements::const_iterator
{
    using ElementType = Elements::value_type;
    using SizeType = Elements::size_type;
    using Itr = Elements::const_iterator;

    SizeType const size{elements.size()};

    if (size < SizeType{3U})
    {
        return elements.cend();
    }

    SizeType threshold{(size / SizeType{2U}) + SizeType{1U}};
    SizeType count{0U};
    ElementType majority_elm{} /*[[indeterminate]]*/;
    Itr majority_itr{} /*[[indeterminate]]*/;

    for (Itr itr{elements.cbegin()}; itr != elements.cend(); ++itr)
    {
        if (count == SizeType{0U})
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

    for (auto itr{elements.cbegin()}; itr != elements.cend(); ++itr)
    {
        if (*itr == majority_elm)
        {
            --threshold;
        }

        if (threshold == SizeType{0U})
        {
            return majority_itr;
        }
    }

    return elements.cend();
}

} // namespace forfun::majority_element

#endif // FORFUN_MAJORITY_ELEMENT_HPP_
