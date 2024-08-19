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
#include <concepts>
#include <iterator>
#include <string_view>

namespace forfun::palindrome {

namespace offset_based {

template <std::integral CharT>
#if __has_cpp_attribute(clang::no_sanitize)
[[clang::no_sanitize("unsigned-integer-overflow")]]
#endif // __has_cpp_attribute(clang::no_sanitize)
[[nodiscard]]
constexpr auto is_palindrome(
    typename std::basic_string_view<CharT>::const_pointer const s,
    typename std::basic_string_view<CharT>::size_type const length
) noexcept -> bool
{
    using SizeType = std::basic_string_view<CharT>::size_type;

    SizeType end{length - 1U};
    SizeType const mid{length / 2U};

    for (SizeType i{0U}; i != mid; ++i)
    {
        if (s[i] != s[end--])
        {
            return false;
        }
    }

    return true;
}

#if __has_cpp_attribute(clang::no_sanitize)
[[clang::no_sanitize("unsigned-integer-overflow")]]
#endif // __has_cpp_attribute(clang::no_sanitize)
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using SizeType = std::string_view::size_type;

    SizeType const length{s.length()};
    SizeType const end{length - 1U};
    SizeType const mid{length / 2U};

    for (SizeType i{0U}; i != mid; ++i)
    {
        if (std::tolower(static_cast<unsigned char>(s[i]))
            != std::tolower(static_cast<unsigned char>(s[end - i])))
        {
            return false;
        }
    }

    return true;
}

} // namespace offset_based

namespace iterator_based {

template <std::integral CharT>
// clang-format off
    requires std::contiguous_iterator<
        typename std::basic_string_view<CharT>::const_iterator>
// clang-format on
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using ConstIter = std::basic_string_view<CharT>::const_iterator;
    using ConstRevIter = std::basic_string_view<CharT>::const_reverse_iterator;
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    SizeType const length{s.length()};
    ConstIter const cbegin{s.cbegin()};
    ConstRevIter upper{s.crbegin()};

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    ConstIter const mid{cbegin + static_cast<DiffType>(length / 2U)};

    for (ConstIter lower{cbegin}; lower != mid; ++lower)
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
    using ConstIter = std::string_view::const_iterator;
    using ConstRevIter = std::string_view::const_reverse_iterator;
    using DiffType = std::string_view::difference_type;

    ConstIter const cbegin{s.cbegin()};
    ConstRevIter upper{s.crbegin()};
    ConstIter const mid{cbegin + static_cast<DiffType>(s.length() / 2U)};

    for (ConstIter lower{cbegin}; lower != mid; ++lower)
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
template <std::integral CharT>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using ConstIter = std::basic_string_view<CharT>::const_iterator;
    using DiffType = std::basic_string_view<CharT>::difference_type;

    ConstIter const cbegin{s.cbegin()};

    return std::equal(
        cbegin, cbegin + static_cast<DiffType>(s.length() / 2U), s.crbegin()
    );
}

namespace bloated {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
template <std::integral CharT>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;

    return std::equal(
        s.cbegin(),
        std::next(s.cbegin(), static_cast<DiffType>(s.length() / 2U)),
        s.crbegin()
    );
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
    using ConstIter = std::string_view::const_iterator;
    using DiffType = std::string_view::difference_type;

    ConstIter const cbegin{s.cbegin()};

    return std::equal(
        cbegin,
        std::next(cbegin, static_cast<DiffType>(s.length() / 2U)),
        s.crbegin(),
        detail::equal_case_insensitive
    );
}

} // namespace bloated

} // namespace functional

} // namespace forfun::palindrome

#endif // FORFUN_PALINDROME_HPP_
