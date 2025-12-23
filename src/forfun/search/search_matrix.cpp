// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/search/search_matrix.hpp"

#include "forfun/search/binary_search.hpp"

#include <functional>
#include <iterator>
#include <vector>

namespace forfun::search::search_matrix {

namespace approach_a {

auto find(
    std::vector<std::vector<int>> const& matrix, int const target
) noexcept -> bool
{
    using std::cbegin;
    using std::cend;
    using std::distance;
    using std::greater;
    using std::less;
    using std::next;

    using DiffType = std::vector<std::vector<int>>::difference_type;

    static constexpr DiffType const two{2};

    auto top_iter{cbegin(matrix)};
    auto btm_iter{cend(matrix)};
    auto num_rows{distance(top_iter, btm_iter)};

    // Row-major approach, where the inner vector is a contiguous row.

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        auto const aux{num_rows};
        auto const row_iter{next(top_iter, aux / two)};

        if (less{}(target, row_iter->back())
            and less{}(target, row_iter->front()))
        {
            btm_iter = row_iter;
            num_rows = (aux / two) + (aux % two);

            continue;
        }

        if (greater{}(target, row_iter->front())
            and greater{}(target, row_iter->back()))
        {
            advance(top_iter, (aux / two) + (aux % two));
            num_rows = aux / two;

            continue;
        }

        // clang-format off
        // Avoid ADL and invoke our find function instead of STL's.
        return forfun::search::binary_search::iterative::find(
            cbegin(*row_iter), cend(*row_iter), target
        ) != cend(*row_iter);
        // clang-format on

    } while (top_iter != btm_iter);

    return false;
}

} // namespace approach_a

namespace approach_b {

auto find(
    std::vector<std::vector<int>> const& matrix, int const target
) noexcept -> bool
{
    using std::cbegin;
    using std::cend;
    using std::distance;
    using std::greater;
    using std::less;
    using std::next;

    using DiffType = std::vector<std::vector<int>>::difference_type;

    static constexpr DiffType const two{2};

    auto top_iter{cbegin(matrix)};
    auto btm_iter{cend(matrix)};

    // Row-major approach, where the inner vector is a contiguous row.

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        auto const num_rows{distance(top_iter, btm_iter)};
        auto const row_iter{next(top_iter, num_rows / two)};

        if (less{}(target, row_iter->back())
            and less{}(target, row_iter->front()))
        {
            btm_iter = row_iter;

            continue;
        }

        if (greater{}(target, row_iter->front())
            and greater{}(target, row_iter->back()))
        {
            advance(top_iter, (num_rows / two) + (num_rows % two));

            continue;
        }

        // clang-format off
        // Avoid ADL and invoke our find function instead of STL's.
        return forfun::search::binary_search::iterative::find(
            cbegin(*row_iter), cend(*row_iter), target
        ) != cend(*row_iter);
        // clang-format on

    } while (top_iter != btm_iter);

    return false;
}

} // namespace approach_b

} // namespace forfun::search::search_matrix
