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
#include <cstddef>
#include <string_view>

namespace forfun::palindrome {

namespace raw {

[[nodiscard]] constexpr inline bool
is_palindrome(std::string_view const& s) noexcept {
    auto const end{s.length() - 1};
    auto const mid{s.length() / 2};

    for (std::size_t i{0}; i < mid; ++i) {
        if (s[i] != s[end - i]) {
            return false;
        }
    }

    return true;
}

[[nodiscard]] inline bool is_palindrome_ci(std::string_view const& s) noexcept {
    auto const end{s.length() - 1};
    auto const mid{s.length() / 2};

    for (std::size_t i{0}; i < mid; ++i) {
        if (std::tolower(static_cast<unsigned char>(s[i]))
            != std::tolower(static_cast<unsigned char>(s[end - i]))) {
            return false;
        }
    }

    return true;
}

} // namespace raw

namespace fast {

[[nodiscard]] constexpr inline bool
is_palindrome(std::string_view const& s) noexcept {
    auto upper{s.cend() - 1};
    auto const mid{s.cbegin() + (s.length() / 2)};

    for (auto lower{s.cbegin()}; lower < mid; ++lower) {
        if ((*lower) != (*upper)) {
            return false;
        }

        --upper;
    }

    return true;
}

[[nodiscard]] inline bool is_palindrome_ci(std::string_view const& s) noexcept {
    auto upper{s.cend() - 1};
    auto const mid{s.cbegin() + (s.length() / 2)};

    for (auto lower{s.cbegin()}; lower < mid; ++lower) {
        if (std::tolower(static_cast<unsigned char>((*lower)))
            != std::tolower(static_cast<unsigned char>((*upper)))) {
            return false;
        }

        --upper;
    }

    return true;
}

} // namespace fast

namespace stl_bloated {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
[[nodiscard]] constexpr inline bool
is_palindrome(std::string_view const& s) noexcept {
    return std::equal(
        s.cbegin(), std::next(s.cbegin(), s.size() / 2), s.crbegin());
}

namespace {
[[nodiscard]] inline bool
equal_case_insensitive(char const a, char const b) noexcept {
    return std::tolower(static_cast<unsigned char>(a))
        == std::tolower(static_cast<unsigned char>(b));
}
} // namespace

[[nodiscard]] inline bool is_palindrome_ci(std::string_view const& s) noexcept {
    return std::equal(
        s.cbegin(), std::next(s.cbegin(), s.size() / 2), s.crbegin(),
        equal_case_insensitive);
}

} // namespace stl_bloated

namespace stl_fast {

/// Adapted from original source:
/// https://en.cppreference.com/w/cpp/algorithm/equal
[[nodiscard]] constexpr inline bool
is_palindrome(std::string_view const& s) noexcept {
    auto const begin{s.cbegin()};
    return std::equal(begin, begin + (s.size() / 2), s.crbegin());
}

} // namespace stl_fast

} // namespace forfun::palindrome

#endif // FORFUN_PALINDROME_HPP_
