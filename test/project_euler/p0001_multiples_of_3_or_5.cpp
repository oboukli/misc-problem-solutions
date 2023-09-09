// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"

#include <cassert>

int main()
{
    {
        int const s{find_sum_mult_three_five(1)};
        assert(s == 0);
    }

    {
        int const s{find_sum_mult_three_five(4)};
        assert(s == 3);
    }

    {
        int const s{find_sum_mult_three_five(6)};
        assert(s == 8);
    }

    {
        int const s{find_sum_mult_three_five(10)};
        assert(s == 23);
    }

    {
        int const s{find_sum_mult_three_five(11)};
        assert(s == 33);
    }

    {
        int const s{find_sum_mult_three_five(1000)};
        assert(s == 233168);
    }

    return 0;
}
