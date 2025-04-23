// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/valid_anagram.hpp"

#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <string_view>

namespace forfun::valid_anagram::char_only {

[[nodiscard]] auto is_anagram(std::string_view s, std::string_view t) noexcept
    -> bool
{
    using Iter = std::string_view::const_iterator;

    if (s.length() != t.length())
    {
        return false;
    }

    std::array<
        std::size_t,
        2U << static_cast<std::size_t>(
            std::numeric_limits<std::string_view::value_type>::digits
        )>
        bucket{};
    static_assert(bucket.size() == std::size_t{256U});

    for (Iter iter{s.cbegin()}; iter != s.cend(); ++iter)
    {
        ++(*std::next(bucket.begin(), *iter));
    }

    for (Iter iter{t.cbegin()}; iter != t.cend(); ++iter)
    {
        auto* const it{std::next(bucket.begin(), *iter)};
        if (*it == std::size_t{0U})
        {
            return false;
        }

        --(*it);
    }

    return true;
}

} // namespace forfun::valid_anagram::char_only
