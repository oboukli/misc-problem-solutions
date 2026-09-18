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
#include <functional>
#include <iterator>
#include <string_view>

namespace forfun::palindrome {

namespace functional {

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
/// @remark Adapted from an example on cppreference.com
/// https://en.cppreference.com/w/cpp/algorithm/equal.
template <std::integral CharT>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    using std::cbegin;
    using std::crbegin;
    using std::next;
    using std::size;

    return std::equal(
        cbegin(s),
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2})),
        crbegin(s)
    );
}

namespace detail {

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto equal_case_insensitive(char const a, char const b) noexcept -> bool
{
    return std::tolower(static_cast<unsigned char>(a))
        == std::tolower(static_cast<unsigned char>(b));
}

} // namespace detail

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using DiffType = std::string_view::difference_type;
    using SizeType = std::string_view::size_type;

    using std::cbegin;
    using std::crbegin;
    using std::next;

    return std::equal(
        cbegin(s),
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2})),
        crbegin(s),
        detail::equal_case_insensitive
    );
}

} // namespace functional

namespace iterator_based {

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
template <std::integral CharT>
    requires std::contiguous_iterator<
        typename std::basic_string_view<CharT>::const_iterator>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    using std::cbegin;
    using std::less;
    using std::next;
    using std::size;

    if (less<>{}(size(s), SizeType{2})) [[unlikely]]
    {
        return true;
    }

    auto upper{next(cbegin(s), static_cast<DiffType>(size(s) - SizeType{1}))};

    auto const mid{
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2}))
    };

    for (auto lower{cbegin(s)}; lower != mid; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        --upper;
    }

    return true;
}

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using DiffType = std::string_view::difference_type;
    using SizeType = std::string_view::size_type;

    using std::cbegin;
    using std::less;
    using std::next;
    using std::size;

    if (less<>{}(size(s), SizeType{2})) [[unlikely]]
    {
        return true;
    }

    auto upper{next(cbegin(s), static_cast<DiffType>(size(s) - SizeType{1}))};

    auto const mid{
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2}))
    };

    for (auto lower{cbegin(s)}; lower != mid; ++lower)
    {
        if (std::tolower(static_cast<unsigned char>(*lower))
            != std::tolower(static_cast<unsigned char>(*upper)))
        {
            return false;
        }

        --upper;
    }

    return true;
}

} // namespace iterator_based

namespace offset_based {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif // __clang__

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
template <std::integral CharT>
[[nodiscard]]
constexpr auto is_palindrome(
    typename std::basic_string_view<CharT>::const_pointer const s,
    typename std::basic_string_view<CharT>::size_type const length
) noexcept -> bool
{
    using SizeType = std::basic_string_view<CharT>::size_type;

    SizeType end{length - 1UZ};
    SizeType const mid{length / 2UZ};

    for (SizeType i{}; i != mid; ++i)
    {
        if (s[i] != s[end--])
        {
            return false;
        }
    }

    return true;
}

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using SizeType = std::string_view::size_type;

    using std::size;

    SizeType const end{size(s) - 1UZ};
    SizeType const mid{size(s) / 2UZ};

    for (SizeType i{}; i != mid; ++i)
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
        if (std::tolower(static_cast<unsigned char>(s[i]))
            != std::tolower(static_cast<unsigned char>(s[end - i])))
        // NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
        {
            return false;
        }
    }

    return true;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

} // namespace offset_based

namespace pointer_based_variant_1 {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif // __clang__

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
template <std::integral CharT>
    requires std::contiguous_iterator<
        typename std::basic_string_view<CharT>::const_iterator>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    using std::data;
    using std::size;

    auto const* upper{data(s) + static_cast<DiffType>(size(s) - SizeType{1})};

    auto const* const mid{
        data(s) + static_cast<DiffType>(size(s) / SizeType{2})
    };

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto const* lower{data(s)}; lower != mid; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        --upper;
    }

    return true;
}

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using DiffType = std::string_view::difference_type;
    using SizeType = std::string_view::size_type;

    using std::data;
    using std::size;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto const* upper{data(s) + static_cast<DiffType>(size(s) - SizeType{1})};

    auto const* const mid{
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        data(s) + static_cast<DiffType>(size(s) / SizeType{2})
    };

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto const* lower{data(s)}; lower != mid; ++lower)
    {
        if (std::tolower(static_cast<unsigned char>(*lower))
            != std::tolower(static_cast<unsigned char>(*upper)))
        {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        --upper;
    }

    return true;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

} // namespace pointer_based_variant_1

namespace pointer_based_variant_2 {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif // __clang__

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
template <std::integral CharT>
    requires std::contiguous_iterator<
        typename std::basic_string_view<CharT>::const_iterator>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    using std::data;
    using std::size;

    auto const* upper{data(s) + static_cast<DiffType>(size(s) - SizeType{1})};

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto const* lower{data(s)}; lower < upper; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        --upper;
    }

    return true;
}

/// @note Undefined behavior when length is zero.
/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using DiffType = std::string_view::difference_type;
    using SizeType = std::string_view::size_type;

    using std::data;
    using std::size;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto const* upper{data(s) + static_cast<DiffType>(size(s) - SizeType{1})};

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto const* lower{data(s)}; lower < upper; ++lower)
    {
        if (std::tolower(static_cast<unsigned char>(*lower))
            != std::tolower(static_cast<unsigned char>(*upper)))
        {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        --upper;
    }

    return true;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

} // namespace pointer_based_variant_2

namespace reverse_iterator_based {

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
template <std::integral CharT>
    requires std::contiguous_iterator<
        typename std::basic_string_view<CharT>::const_iterator>
[[nodiscard]]
constexpr auto is_palindrome(std::basic_string_view<CharT> const s) noexcept
    -> bool
{
    using DiffType = std::basic_string_view<CharT>::difference_type;
    using SizeType = std::basic_string_view<CharT>::size_type;

    using std::cbegin;
    using std::crbegin;
    using std::next;
    using std::size;

    auto upper{crbegin(s)};

    auto const mid{
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2}))
    };

    for (auto lower{cbegin(s)}; lower != mid; ++lower)
    {
        if ((*lower) != (*upper))
        {
            return false;
        }

        ++upper;
    }

    return true;
}

/// @note Assumes single-byte character encoded strings. Undefined behavior for
/// multi-byte character encodings.
[[nodiscard]]
inline auto is_palindrome_ci(std::string_view const s) noexcept -> bool
{
    using DiffType = std::string_view::difference_type;
    using SizeType = std::string_view::size_type;

    using std::cbegin;
    using std::crbegin;
    using std::next;
    using std::size;

    auto upper{crbegin(s)};
    auto const mid{
        next(cbegin(s), static_cast<DiffType>(size(s) / SizeType{2}))
    };

    for (auto lower{cbegin(s)}; lower != mid; ++lower)
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

} // namespace reverse_iterator_based

} // namespace forfun::palindrome

#endif // FORFUN_PALINDROME_HPP_
