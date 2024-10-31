// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/fizzbuzz.hpp"

#include <ios>
#include <sstream>
#include <string>

namespace forfun::fizzbuzz {

[[nodiscard]] auto fizzbuzz(int const n) -> std::string
{
    std::ostringstream stream;
    for (int i{1}; i <= n; ++i)
    {
        bool is_numeric{true};

        if ((i % 3) == 0)
        {
            stream.write("Fizz", std::streamsize{4});

            is_numeric = false;
        }

        if ((i % 5) == 0)
        {
            stream.write("Buzz", std::streamsize{4});
        }
        else if (is_numeric)
        {
            stream << i;
        }
    }

    return stream.str();
}

} // namespace forfun::fizzbuzz
