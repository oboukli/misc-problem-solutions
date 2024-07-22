// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/valid_anagram.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <string_view>

namespace forfun::valid_anagram::char_only {

[[nodiscard]] auto
is_anagram(std::string_view s, std::string_view t) noexcept -> bool
{
    using Iter = std::string_view::const_iterator;

    if (s.length() != t.length())
    {
        return false;
    }

    std::array<
        std::size_t,
        2U << static_cast<std::size_t>(
            std::numeric_limits<std::string_view::value_type>::digits)>
        haystack{};
    static_assert(haystack.size() == std::size_t{256U});

    for (Iter iter{s.cbegin()}; iter != s.cend(); ++iter)
    {
        auto const index{
            static_cast<std::size_t>(static_cast<unsigned char>(*iter))};
        assert((std::size_t{0U} <= index) and (index < haystack.size()));

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        ++haystack[index];
    }

    for (Iter iter{t.cbegin()}; iter != t.cend(); ++iter)
    {
        auto const index{
            static_cast<std::size_t>(static_cast<unsigned char>(*iter))};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        if (haystack[index] == std::size_t{0U})
        {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        --haystack[index];
    }

    return true;
}

} // namespace forfun::valid_anagram::char_only
