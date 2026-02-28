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
    using std::cbegin;
    using std::cend;
    using std::size;

    using ElementType = Elements::value_type;
    using SizeType = Elements::size_type;
    using Iter = Elements::const_iterator;

    SizeType const elements_size{size(elements)};

    if (elements_size < SizeType{3})
    {
        return cend(elements);
    }

    SizeType threshold{(elements_size / SizeType{2}) + SizeType{1}};
    SizeType count{0};
    ElementType majority_elm{} /*[[indeterminate]]*/;
    Iter majority_iter{} /*[[indeterminate]]*/;

    for (Iter iter{cbegin(elements)}; iter != cend(elements); ++iter)
    {
        if (count == SizeType{})
        {
            majority_elm = *iter;
            majority_iter = iter;
        }

        if (*iter == majority_elm)
        {
            ++count;
            if (count == threshold)
            {
                return majority_iter;
            }
        }
        else
        {
            --count;
        }
    }

    for (auto iter{cbegin(elements)}; iter != cend(elements); ++iter)
    {
        if (*iter == majority_elm)
        {
            --threshold;
        }

        if (threshold == SizeType{})
        {
            return majority_iter;
        }
    }

    return cend(elements);
}

} // namespace forfun::majority_element

#endif // FORFUN_MAJORITY_ELEMENT_HPP_
