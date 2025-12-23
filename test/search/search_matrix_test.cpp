// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/search/search_matrix.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Search matrix",
    "[search_matrix]",
    (auto find, find),
    forfun::search::search_matrix::approach_a::find,
    forfun::search::search_matrix::approach_b::find
)
{
    SECTION("One-by-one matrix has target")
    {
        static constexpr int const target{0};
        std::vector<std::vector<int>> const matrix{{0}};

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("One-by-one matrix, does not have target")
    {
        static constexpr int const target{9};
        std::vector<std::vector<int>> const matrix{{11}};

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }

    SECTION("Odd by odd, has target in last row")
    {
        static constexpr int const target{16};
        std::vector<std::vector<int>> const matrix{
            {2, 4, 6},
            {8, 10, 12},
            {14, 16, 18},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("Odd by odd, does not have target in last row")
    {
        static constexpr int const target{13};
        std::vector<std::vector<int>> const matrix{
            {2, 4, 6},
            {8, 10, 12},
            {14, 16, 18},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }

    SECTION("Even by even, has target in second row")
    {
        static constexpr int const target{12};
        std::vector<std::vector<int>> const matrix{
            {2, 4, 6, 8},
            {10, 12, 14, 16},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("Even by even, does not have target")
    {
        static constexpr int const target{19};
        std::vector<std::vector<int>> const matrix{
            {2, 4, 6, 8},
            {10, 12, 14, 16},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }

    SECTION("Eight-by-eight, has target (benchmark case)")
    {
        static constexpr int const target{397};
        std::vector<std::vector<int>> const matrix{
            {101, 103, 107, 109, 113, 127, 131, 137},
            {139, 149, 151, 157, 163, 167, 173, 179},
            {181, 191, 193, 197, 199, 211, 223, 227},
            {229, 233, 239, 241, 251, 257, 263, 269},
            {271, 277, 281, 283, 293, 307, 311, 313},
            {317, 331, 337, 347, 349, 353, 359, 367},
            {373, 379, 383, 389, 397, 401, 409, 419},
            {421, 431, 433, 439, 443, 449, 457, 461},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("Eight-by-eight, does not have target")
    {
        static constexpr int const target{52};
        std::vector<std::vector<int>> const matrix{
            {101, 103, 107, 109, 113, 127, 131, 137},
            {139, 149, 151, 157, 163, 167, 173, 179},
            {181, 191, 193, 197, 199, 211, 223, 227},
            {229, 233, 239, 241, 251, 257, 263, 269},
            {271, 277, 281, 283, 293, 307, 311, 313},
            {317, 331, 337, 347, 349, 353, 359, 367},
            {373, 379, 383, 389, 397, 401, 409, 419},
            {421, 431, 433, 439, 443, 449, 457, 461},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }

    SECTION("LeetCode case 1")
    {
        static constexpr int const target{3};
        std::vector<std::vector<int>> const matrix{
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("LeetCode case 2")
    {
        static constexpr int const target{13};
        std::vector<std::vector<int>> const matrix{
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }

    SECTION("NeetCode case 1")
    {
        static constexpr int const target{10};
        std::vector<std::vector<int>> const matrix{
            {1, 2, 4, 8},
            {10, 11, 12, 13},
            {14, 20, 30, 40},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE(find(matrix, target));
    }

    SECTION("NeetCode case 2")
    {
        static constexpr int const target{15};
        std::vector<std::vector<int>> const matrix{
            {1, 2, 4, 8},
            {10, 11, 12, 13},
            {14, 20, 30, 40},
        };

        CAPTURE(matrix);
        CAPTURE(target);

        REQUIRE_FALSE(find(matrix, target));
    }
}

// References:
// https://leetcode.com/problems/search-a-2d-matrix/
// https://neetcode.io/problems/search-2d-matrix/
