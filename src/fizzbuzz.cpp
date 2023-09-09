// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/fizzbuzz.hpp"

#include <sstream>
#include <string>

std::string fizzbuzz(int const n) noexcept
{
    std::ostringstream buffer;
    for (int i{1}; i <= n; ++i)
    {
        bool f{true};

        if (i % 3 == 0)
        {
            buffer << "Fizz";
            f = false;
        }

        if (i % 5 == 0)
        {
            buffer << "Buzz";
        }
        else if (f)
        {
            buffer << i;
        }
    }

    return buffer.str();
}
