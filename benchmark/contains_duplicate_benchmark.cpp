// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains duplicate benchmarking", "[benchmark][contains_duplicate]")
{
    using namespace forfun::contains_duplicate;

    using Iter = std::array<int, 256>::iterator;

    std::array primes{
        293,  1321, 1171, 229,  787,  181,  1361, 1259, 1511, 1367, 929,  103,
        761,  269,  1277, 109,  191,  271,  347,  1409, 1163, 881,  1523, 631,
        1489, 97,   937,  131,  1373, 139,  431,  701,  1543, 313,  1109, 709,
        601,  251,  7,    383,  163,  433,  953,  11,   719,  599,  3,    641,
        1187, 151,  311,  449,  587,  1283, 419,  1151, 811,  523,  647,  1229,
        827,  1427, 1597, 1087, 373,  727,  1201, 487,  1297, 1129, 1069, 199,
        179,  1289, 521,  571,  127,  911,  1213, 1493, 1103, 1033, 1301, 67,
        461,  349,  677,  1051, 1429, 967,  1193, 41,   1549, 613,  443,  829,
        337,  467,  71,   1291, 101,  1231, 1181, 617,  317,  941,  37,   859,
        421,  211,  439,  1117, 769,  1567, 1097, 1481, 59,   971,  157,  643,
        499,  1031, 29,   1619, 89,   577,  1013, 31,   367,  919,  83,   263,
        1433, 947,  463,  683,  241,  17,   491,  61,   23,   1423, 1279, 1453,
        1399, 1153, 997,  607,  569,  43,   5,    397,  1559, 47,   751,  173,
        883,  733,  983,  877,  823,  757,  809,  509,  1123, 991,  1571, 773,
        1303, 1471, 659,  53,   557,  1019, 13,   887,  79,   257,  619,  73,
        1061, 113,  1327, 1607, 1237, 907,  743,  1223, 503,  821,  563,  359,
        1439, 853,  661,  457,  107,  1091, 797,  863,  401,  1249, 409,  1217,
        1307, 1319, 1009, 283,  233,  239,  1447, 1583, 691,  739,  977,  1459,
        653,  1039, 149,  331,  389,  1483, 1531, 277,  479,  281,  1063, 19,
        839,  167,  1579, 1609, 307,  857,  673,  1499, 193,  547,  353,  379,
        1451, 1613, 1049, 1553, 1093, 1601, 137,  1487, 197,  593,  2,    541,
        1021, 227,  223,  1381
    };

    static_assert(primes.size() == 256UZ);

    ankerl::nanobench::Bench()

        .title("Contains duplicate")
        .relative(true)

        .run(
            NAMEOF_RAW(adjacent_find_based::contains_duplicate<Iter, Iter>)
                .c_str(),
            [&primes] noexcept -> void {
                ankerl::nanobench::doNotOptimizeAway(
                    adjacent_find_based::contains_duplicate(
                        primes.begin(), primes.end()
                    )
                );
            }
        )

        .run(
            NAMEOF_RAW(quadratic::contains_duplicate<Iter, Iter>).c_str(),
            [&primes] noexcept -> void {
                ankerl::nanobench::doNotOptimizeAway(
                    quadratic::contains_duplicate(
                        primes.cbegin(), primes.cend()
                    )
                );
            }
        )

        .run(
            NAMEOF_RAW(sorted::contains_duplicate<Iter, Iter>).c_str(),
            [&primes] noexcept -> void {
                ankerl::nanobench::doNotOptimizeAway(
                    sorted::contains_duplicate(primes.begin(), primes.end())
                );
            }
        )

        .run(
            NAMEOF_RAW(unordered_set_based::contains_duplicate<Iter, Iter>)
                .c_str(),
            [&primes] noexcept -> void {
                ankerl::nanobench::doNotOptimizeAway(
                    unordered_set_based::contains_duplicate(
                        primes.begin(), primes.end()
                    )
                );
            }
        )

        ;
}
