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
    auto addend_a_iter{addend_a.cbegin()};
    auto const addend_a_end{addend_a.cend()};

    auto addend_b_iter{addend_b.cbegin()};
    auto const addend_b_end{addend_b.cend()};

    std::forward_list<unsigned int> result{};
    auto back_iter{result.before_begin()};

    unsigned int carry{0U};
    unsigned int column_sum{0U};
    while ((addend_a_iter != addend_a_end) || (addend_b_iter != addend_b_end))
    {
        if (addend_a_iter != addend_a_end)
        {
            assert(*addend_a_iter <= 9U);
            column_sum += *addend_a_iter++;
        }

        if (addend_b_iter != addend_b_end)
        {
            assert(*addend_b_iter <= 9U);
            column_sum += *addend_b_iter++;
        }

        // NOLINTNEXTLINE (cppcoreguidelines-avoid-magic-numbers)
        back_iter = result.insert_after(back_iter, column_sum % 10U);
        // NOLINTNEXTLINE (cppcoreguidelines-avoid-magic-numbers)
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
