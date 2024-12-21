// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/add_two_numbers.hpp"

#include <cassert>
#include <forward_list>

namespace forfun::add_two_numbers::stl {

[[nodiscard]] auto add_two_numbers(
    std::forward_list<unsigned int> const& addend_a,
    std::forward_list<unsigned int> const& addend_b
) noexcept -> std::forward_list<unsigned int>
{
    auto iter_a{addend_a.cbegin()};
    auto iter_b{addend_b.cbegin()};

    std::forward_list<unsigned int> result{};
    auto back_iter{result.before_begin()};

    unsigned int carry{0U};
    unsigned int column_sum{0U};

    while ((iter_a != addend_a.cend()) || (iter_b != addend_b.cend()))
    {
        if (iter_a != addend_a.cend())
        {
            assert(*iter_a <= 9U);
            column_sum += *iter_a++;
        }

        if (iter_b != addend_b.cend())
        {
            assert(*iter_b <= 9U);
            column_sum += *iter_b++;
        }

        back_iter = result.insert_after(back_iter, column_sum % 10U);
        carry = column_sum / 10U;
        column_sum = carry;
    }

    if (carry != 0U)
    {
        result.insert_after(back_iter, carry);
    }

    return result;
}

} // namespace forfun::add_two_numbers::stl
