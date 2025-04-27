// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// References:
/// https://en.wikipedia.org/wiki/Anagram
/// https://leetcode.com/problems/valid-anagram/

#ifndef FORFUN_VALID_ANAGRAM_HPP_
#define FORFUN_VALID_ANAGRAM_HPP_

#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <string_view>

namespace forfun::valid_anagram {

namespace char_only {

[[nodiscard]] constexpr auto
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
        decltype(bucket)::iterator const it{std::next(bucket.begin(), *iter)};
        if (*it == std::size_t{0U})
        {
            return false;
        }

        --(*it);
    }

    return true;
}

} // namespace char_only

namespace map_based {

template <std::integral CharT>
[[nodiscard]] auto
is_anagram(std::basic_string_view<CharT> s, std::basic_string_view<CharT> t)
    -> bool
{
    using Iter = std::basic_string_view<CharT>::const_iterator;

    if (s.length() != t.length())
    {
        return false;
    }

    std::map<CharT, std::size_t> bucket{};

    for (Iter iter{s.cbegin()}; iter != s.cend(); ++iter)
    {
        ++bucket[*iter];
    }

    for (Iter iter{t.cbegin()}; iter != t.cend(); ++iter)
    {
        if (bucket[*iter] == std::size_t{0})
        {
            return false;
        }

        --bucket[*iter];
    }

    return true;
}

} // namespace map_based

namespace multiset_based {

template <std::integral CharT>
[[nodiscard]] auto
is_anagram(std::basic_string_view<CharT> s, std::basic_string_view<CharT> t)
    -> bool
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

} // namespace multiset_based

} // namespace forfun::valid_anagram

#endif // FORFUN_VALID_ANAGRAM_HPP_
