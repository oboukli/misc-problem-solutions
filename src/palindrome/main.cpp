// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// Problem source:
// https://en.wikipedia.org/wiki/Palindrome

#include <cctype>
#include <concepts>
#include <string>

template <typename T = std::string, std::integral Tsize = typename T::size_type>
[[nodiscard]] bool is_palindrome(const T& s) noexcept {
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

int main() {
    using namespace std::string_literals;

    {
        bool const f_palindrome{is_palindrome(""s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("\xb8Y\xb8"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("aba"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("a b a"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("101"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("Aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("Aab4'{x{'4BaA"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("dummy"s)};
        assert(f_palindrome == false);
    }

    return 0;
}
