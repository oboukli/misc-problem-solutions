// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem reference:
/// https://en.wikipedia.org/wiki/Palindrome

#ifndef FORFUN_PALINDROME_HPP_
#define FORFUN_PALINDROME_HPP_

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string_view>

namespace forfun::palindrome {

namespace raw {

template <typename CharT>
[[clang::no_sanitize("unsigned-integer-overflow")]] [[nodiscard]]
constexpr auto
is_palindrome(std::basic_string_view<CharT> const s) noexcept -> bool
{
    using SizeType = decltype(s)::size_type;

    auto const end{s.length() - 1};
    auto const mid{s.length() / 2};

    for (SizeType i{0}; i < mid; ++i)
    {
        if (s[i] != s[end - i])
        {
            return false;
        }
    }

    return true;
}

[[clang::no_sanitize("unsigned-integer-overflow")]] [[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    auto const end{s.length() - 1};
    auto const mid{s.length() / 2};

    for (std::string_view::size_type i{0}; i < mid; ++i)
    {
        if (std::tolower(static_cast<unsigned char>(s[i]))
            != std::tolower(static_cast<unsigned char>(s[end - i])))
        {
            return false;
        }
    }

    return true;
}

} // namespace raw

namespace iterator_based {

template <typename CharT>
[[nodiscard]]
constexpr auto
is_palindrome(std::basic_string_view<CharT> const s) noexcept -> bool
{
    using ConstItr = decltype(s)::const_iterator;

    auto upper{s.crbegin()};
    ConstItr const mid{s.cbegin() + (s.length() / 2)};

    for (ConstItr lower{s.cbegin()}; lower < mid; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        ++upper;
    }

    return true;
}

[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using ConstItr = decltype(s)::const_iterator;

    auto upper{s.crbegin()};
    ConstItr const mid{s.cbegin() + (s.length() / 2)};

    for (ConstItr lower{s.cbegin()}; lower < mid; ++lower)
    {
        if (std::tolower(static_cast<unsigned char>(*lower))
            != std::tolower(static_cast<unsigned char>(*upper)))
        {
            return false;
        }

        ++upper;
    }

    return true;
}

} // namespace iterator_based

namespace functional {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
template <typename CharT>
[[nodiscard]]
constexpr auto
is_palindrome(std::basic_string_view<CharT> const s) noexcept -> bool
{
    using ConstItr = decltype(s)::const_iterator;

    ConstItr const begin{s.cbegin()};
    return std::equal(begin, begin + (s.size() / 2), s.crbegin());
}

namespace bloated {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
template <typename CharT>
[[nodiscard]]
constexpr auto
is_palindrome(std::basic_string_view<CharT> const s) noexcept -> bool
{
    return std::equal(
        s.cbegin(),
        std::next(
            s.cbegin(),
            static_cast<decltype(s)::difference_type>(s.size() / 2)),
        s.crbegin());
}

namespace detail {

[[nodiscard]]
inline auto equal_case_insensitive(char const a, char const b) noexcept -> bool
{
    return std::tolower(static_cast<unsigned char>(a))
        == std::tolower(static_cast<unsigned char>(b));
}

} // namespace detail

[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    return std::equal(
        s.cbegin(),
        std::next(
            s.cbegin(),
            static_cast<decltype(s)::difference_type>(s.size() / 2)),
        s.crbegin(),
        detail::equal_case_insensitive);
}

} // namespace bloated

} // namespace functional

} // namespace forfun::palindrome

#endif // FORFUN_PALINDROME_HPP_
