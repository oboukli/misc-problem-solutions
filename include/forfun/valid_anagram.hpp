// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// References:
/// https://en.wikipedia.org/wiki/Anagram
/// https://leetcode.com/problems/valid-anagram/description/

#ifndef FORFUN_VALID_ANAGRAM_HPP_
#define FORFUN_VALID_ANAGRAM_HPP_

#include <concepts>
#include <set>
#include <string_view>

namespace forfun::valid_anagram {

namespace char_only {

[[nodiscard]] auto
is_anagram(std::string_view s, std::string_view t) noexcept -> bool;

} // namespace char_only

namespace generic {

template <std::integral CharT>
[[nodiscard]] auto is_anagram(
    std::basic_string_view<CharT> s,
    std::basic_string_view<CharT> t) noexcept -> bool
{
    using Iter = std::basic_string_view<CharT>::const_iterator;

    if (s.length() != t.length())
    {
        return false;
    }

    std::multiset<typename std::basic_string_view<CharT>::value_type>
        haystack{};

    if constexpr (requires { haystack.insert_range(s); })
    {
        haystack.insert_range(s);
    }
    else
    {
        for (Iter iter{s.cbegin()}; iter != s.cend(); ++iter)
        {
            haystack.emplace(*iter);
        }
    }

    for (Iter iter{t.cbegin()}; iter != t.cend(); ++iter)
    {
        if (auto const nh{haystack.extract(*iter)}; nh.empty())
        {
            return false;
        }
    }

    return true;
}

} // namespace generic

} // namespace forfun::valid_anagram

#endif // FORFUN_VALID_ANAGRAM_HPP_
