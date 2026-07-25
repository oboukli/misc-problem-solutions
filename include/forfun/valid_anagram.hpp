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
#include <map>
#include <set>
#include <string_view>

#include "forfun/common/limits.hpp"

namespace forfun::valid_anagram {

namespace char_only {

[[nodiscard]] constexpr auto
is_anagram(std::string_view const str_a, std::string_view const str_b) noexcept
    -> bool
{
    using Iter = std::string_view::const_iterator;

    if (str_a.length() != str_b.length())
    {
        return false;
    }

    std::array<
        std::size_t,
        forfun::common::limits::domain_size<std::string_view::value_type>()>
        bucket{};
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    static_assert(bucket.size() == 256UZ);

    for (Iter iter{str_a.cbegin()}; iter != str_a.cend(); ++iter)
    {
        ++(*std::next(bucket.begin(), *iter));
    }

    for (Iter iter{str_b.cbegin()}; iter != str_b.cend(); ++iter)
    {
        decltype(bucket)::iterator const bucket_iter{
            std::next(bucket.begin(), *iter)
        };
        if (*bucket_iter == 0UZ)
        {
            return false;
        }

        --(*bucket_iter);
    }

    return true;
}

} // namespace char_only

namespace map_based {

template <std::integral CharT>
[[nodiscard]] auto is_anagram(
    std::basic_string_view<CharT> str_a, std::basic_string_view<CharT> str_b
) -> bool
{
    using Iter = std::basic_string_view<CharT>::const_iterator;

    if (str_a.length() != str_b.length())
    {
        return false;
    }

    std::map<CharT, std::size_t> bucket{};

    for (Iter iter{str_a.cbegin()}; iter != str_a.cend(); ++iter)
    {
        ++bucket[*iter];
    }

    for (Iter iter{str_b.cbegin()}; iter != str_b.cend(); ++iter)
    {
        if (bucket[*iter] == 0UZ)
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
[[nodiscard]] auto is_anagram(
    std::basic_string_view<CharT> str_a, std::basic_string_view<CharT> str_b
) -> bool
{
    using Iter = std::basic_string_view<CharT>::const_iterator;

    if (str_a.length() != str_b.length())
    {
        return false;
    }

    std::multiset<CharT> bucket{};

    if constexpr (requires { bucket.insert_range(str_a); })
    {
        bucket.insert_range(str_a);
    }
    else
    {
        for (Iter iter{str_a.cbegin()}; iter != str_a.cend(); ++iter)
        {
            bucket.emplace(*iter);
        }
    }

    for (Iter iter{str_b.cbegin()}; iter != str_b.cend(); ++iter)
    {
        if (auto const aux{bucket.extract(*iter)}; aux.empty())
        {
            return false;
        }
    }

    return true;
}

} // namespace multiset_based

} // namespace forfun::valid_anagram

#endif // FORFUN_VALID_ANAGRAM_HPP_
