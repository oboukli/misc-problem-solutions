// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <utility>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/last_stone_weight.hpp"

namespace {

using Iter = std::vector<int>::iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Last stone weight (iterator-based strategies)",
    "[last_stone_weight]",
    (auto last_stone_weight, last_stone_weight),
    (forfun::last_stone_weight::heapified::last_stone_weight<Iter, Iter>),
    (forfun::last_stone_weight::naive::last_stone_weight<Iter, Iter>),
    (forfun::last_stone_weight::sort_based::last_stone_weight<Iter, Iter>)
)
{
    SECTION("One element; Element is positive non-zero")
    {
        std::vector stones{17};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 17);
    }

    SECTION("Two ones")
    {
        std::vector stones{1, 1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three ones")
    {
        std::vector stones{1, 1, 1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("Two equal elements")
    {
        std::vector stones{19, 19};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three equal elements")
    {
        std::vector stones{13, 13, 13};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 13);
    }

    SECTION("Four equal elements")
    {
        std::vector stones{17, 17, 17, 17};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Two non-equal elements")
    {
        std::vector stones{2, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 5);
    }

    SECTION("Three non-equal elements evaluating to zero")
    {
        std::vector stones{5, 2, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three non-equal elements evaluating to non-zero")
    {
        std::vector stones{8, 5, 7};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 4);
    }

    SECTION("Four arbitrary elements evaluating to zero")
    {
        std::vector stones{4, 10, 5, 9};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Four arbitrary elements evaluating to non-zero")
    {
        std::vector stones{2, 4, 7, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("Five arbitrary elements evaluating to zero")
    {
        std::vector stones{2, 4, 7, 3, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Five arbitrary elements evaluating to non-zero")
    {
        std::vector stones{4, 5, 7, 5, 8};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 3);
    }

    SECTION("Sixty-four positive non-zero elements (benchmark case)")
    {
        std::vector stones{
            2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
            43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101,
            103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
            173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
            241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
        };

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("One element; Element is zero")
    {
        std::vector stones{0};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Two elements, all of which are zero")
    {
        std::vector stones{0, 0};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Three elements, all of which are zero")
    {
        std::vector stones{0, 0, 0};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
    }

    SECTION("Two elements, one of which is zero")
    {
        std::vector stones{0, 3};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 3);
    }

    SECTION("Trailing zero")
    {
        std::vector stones{3, 0};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 3);
    }

    SECTION("LeetCode test case 1")
    {
        std::vector stones{2, 7, 4, 1, 8, 1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("LeetCode test case 2")
    {
        std::vector stones{1};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("NeetCode test case 1")
    {
        std::vector stones{2, 3, 6, 2, 4};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }

    SECTION("NeetCode test case 2")
    {
        std::vector stones{1, 2};

        CAPTURE(stones);

        REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 1);
    }
}

TEST_CASE(
    "Last stone weight (priority_queue_based::last_stone_weight)",
    "[last_stone_weight]"
)
{
    using forfun::last_stone_weight::priority_queue_based::last_stone_weight;

    SECTION("One element; Element is positive non-zero")
    {
        std::vector stones{17};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 17);
    }

    SECTION("Two ones")
    {
        std::vector stones{1, 1};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Three ones")
    {
        std::vector stones{1, 1, 1};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("Two equal elements")
    {
        std::vector stones{19, 19};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Three equal elements")
    {
        std::vector stones{13, 13, 13};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 13);
    }

    SECTION("Four equal elements")
    {
        std::vector stones{17, 17, 17, 17};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Two non-equal elements")
    {
        std::vector stones{2, 7};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 5);
    }

    SECTION("Three non-equal elements evaluating to zero")
    {
        std::vector stones{5, 2, 7};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Three non-equal elements evaluating to non-zero")
    {
        std::vector stones{8, 5, 7};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 4);
    }

    SECTION("Four arbitrary elements evaluating to zero")
    {
        std::vector stones{4, 10, 5, 9};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Four arbitrary elements evaluating to non-zero")
    {
        std::vector stones{2, 4, 7, 8};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("Five arbitrary elements evaluating to zero")
    {
        std::vector stones{2, 4, 7, 3, 8};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Five arbitrary elements evaluating to non-zero")
    {
        std::vector stones{4, 5, 7, 5, 8};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 3);
    }

    SECTION("Sixty-four positive non-zero elements (benchmark case)")
    {
        std::vector stones{
            2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
            43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101,
            103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
            173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
            241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
        };

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("One element; Element is zero")
    {
        std::vector stones{0};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Two elements, all of which are zero")
    {
        std::vector stones{0, 0};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Three elements, all of which are zero")
    {
        std::vector stones{0, 0, 0};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 0);
    }

    SECTION("Two elements, one of which is zero")
    {
        std::vector stones{0, 3};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 3);
    }

    SECTION("Trailing zero")
    {
        std::vector stones{3, 0};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 3);
    }

    SECTION("LeetCode test case 1")
    {
        std::vector stones{2, 7, 4, 1, 8, 1};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("LeetCode test case 2")
    {
        std::vector stones{1};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("NeetCode test case 1")
    {
        std::vector stones{2, 3, 6, 2, 4};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }

    SECTION("NeetCode test case 2")
    {
        std::vector stones{1, 2};

        CAPTURE(stones);

        int const actual{last_stone_weight(std::move(stones))};
        REQUIRE(actual == 1);
    }
}

TEST_CASE(
    "Last stone weight (heapified strategy empty container degenerate case)",
    "[last_stone_weight]"
)
{
    using forfun::last_stone_weight::heapified::last_stone_weight;

    std::vector<int> stones{};

    CAPTURE(stones);

    REQUIRE(last_stone_weight(stones.begin(), stones.end()) == 0);
}

TEST_CASE(
    "Last stone weight (priority-queue based empty container degenerate case)",
    "[last_stone_weight]"
)
{
    using forfun::last_stone_weight::priority_queue_based::last_stone_weight;

    std::vector<int> stones{};

    CAPTURE(stones);

    REQUIRE(last_stone_weight(std::move(stones)) == 0);
}
