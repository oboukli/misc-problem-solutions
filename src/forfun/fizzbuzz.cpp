// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/fizzbuzz.hpp"

#include <cstdint>
#include <ostream>
#include <string_view>

namespace forfun::fizzbuzz::basic {

auto fizzbuzz(int const n, std::ostream& stream) -> void
{
    using std::data;
    using std::size;

    static constexpr int const fizz_divider{3};
    static constexpr int const buzz_divider{5};
    static constexpr std::string_view const fizz{"Fizz"};
    static constexpr std::string_view const buzz{"Buzz"};

    for (std::intmax_t i{1}; i <= n; ++i)
    {
        bool is_numeric{true};

        if ((i % fizz_divider) == 0)
        {
            stream.write(data(fizz), size(fizz));

            is_numeric = false;
        }

        if ((i % buzz_divider) == 0)
        {
            stream.write(data(buzz), size(buzz));
        }
        else if (is_numeric)
        {
            stream << i;
        }
    }
}

} // namespace forfun::fizzbuzz::basic
