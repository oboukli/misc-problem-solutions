// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindrome.hpp"

#include <cassert>
#include <functional>
#include <string>
#include <string_view>

namespace {

using is_palindrome_func_t = std::function<bool(std::string_view const&)>;

void test_palindrome(is_palindrome_func_t is_palindrome_func)
{
    using namespace std::string_literals;

    {
        bool const f_palindrome{is_palindrome_func(""s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("\xb8Y\xb8"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("aba"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("a b a"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("101"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("tattarrattat"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("dummy"s)};
        assert(f_palindrome == false);
    }
}

void test_palindrome_ci(is_palindrome_func_t is_palindrome_func)
{
    using namespace std::string_literals;

    {
        bool const f_palindrome{is_palindrome_func("Aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome_func("Aab4'{x{'4BaA"s)};
        assert(f_palindrome);
    }
}

} // namespace

int main()
{
    test_palindrome(forfun::palindrome::raw::is_palindrome);
    test_palindrome(forfun::palindrome::fast::is_palindrome);
    test_palindrome(forfun::palindrome::stl_bloated::is_palindrome);
    test_palindrome(forfun::palindrome::stl_fast::is_palindrome);

    test_palindrome_ci(forfun::palindrome::raw::is_palindrome_ci);
    test_palindrome_ci(forfun::palindrome::fast::is_palindrome_ci);
    test_palindrome_ci(forfun::palindrome::stl_bloated::is_palindrome_ci);

    return 0;
}
