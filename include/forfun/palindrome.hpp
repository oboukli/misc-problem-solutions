// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Palindrome

#ifndef FORFUN_PALINDROME_HPP_
#define FORFUN_PALINDROME_HPP_

#include <cctype>
#include <concepts>
#include <string>

template <typename T = std::string, std::integral Tsize = typename T::size_type>
[[nodiscard]] bool is_palindrome(T const& s) noexcept {
    Tsize const len = (s.length()) / Tsize{2};
    auto begin = s.cbegin();
    auto end = --(s.cend());

    for (Tsize i{0}; i < len; ++i) {
        if (std::tolower(static_cast<unsigned char>(*begin))
            != std::tolower(static_cast<unsigned char>(*end))) {
            return false;
        }

        ++begin;
        --end;
    }

    return true;
}

#endif // FORFUN_PALINDROME_HPP_
