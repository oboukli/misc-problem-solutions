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

[[clang::no_sanitize("unsigned-integer-overflow")]] [[nodiscard]] constexpr auto
is_palindrome(std::string_view const& s) noexcept -> bool
{
    auto const end{s.length() - 1};
    auto const mid{s.length() / 2};

    for (std::string_view::size_type i{0}; i < mid; ++i)
    {
        if (s[i] != s[end - i])
        {
            return false;
        }
    }

    return true;
}

[[clang::no_sanitize("unsigned-integer-overflow")]] [[nodiscard]] inline auto
is_palindrome_ci(std::string_view const& s) noexcept -> bool
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

namespace fast {

[[nodiscard]] constexpr auto
is_palindrome(std::string_view const& s) noexcept -> bool
{
    using const_itr = std::string_view::const_iterator;

    auto upper{s.crbegin()};
    const_itr const mid{s.cbegin() + (s.length() / 2)};

    for (const_itr lower{s.cbegin()}; lower < mid; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        ++upper;
    }

    return true;
}

[[nodiscard]] inline auto
is_palindrome_ci(std::string_view const& s) noexcept -> bool
{
    using const_itr = std::string_view::const_iterator;

    auto upper{s.crbegin()};
    const_itr const mid{s.cbegin() + (s.length() / 2)};

    for (const_itr lower{s.cbegin()}; lower < mid; ++lower)
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

} // namespace fast

namespace stl_bloated {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
[[nodiscard]] constexpr auto
is_palindrome(std::string_view const& s) noexcept -> bool
{
    return std::equal(
        s.cbegin(),
        std::next(
            s.cbegin(),
            static_cast<std::string_view::difference_type>(s.size() / 2)),
        s.crbegin());
}

namespace detail {

[[nodiscard]] inline auto
equal_case_insensitive(char const a, char const b) noexcept -> bool
{
    return std::tolower(static_cast<unsigned char>(a))
        == std::tolower(static_cast<unsigned char>(b));
}

} // namespace detail

[[nodiscard]] inline auto
is_palindrome_ci(std::string_view const& s) noexcept -> bool
{
    return std::equal(
        s.cbegin(),
        std::next(
            s.cbegin(),
            static_cast<std::string_view::difference_type>(s.size() / 2)),
        s.crbegin(),
        detail::equal_case_insensitive);
}

} // namespace stl_bloated

namespace stl_fast {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
[[nodiscard]] constexpr auto
is_palindrome(std::string_view const& s) noexcept -> bool
{
    std::string_view::const_iterator const begin{s.cbegin()};
    return std::equal(begin, begin + (s.size() / 2), s.crbegin());
}

} // namespace stl_fast

} // namespace forfun::palindrome

#endif // FORFUN_PALINDROME_HPP_
