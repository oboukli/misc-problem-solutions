// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/array_concatenation.hpp"

TEST_CASE(
    "array_concatenation benchmarking", "[benchmark][array_concatenation]"
)
{
    using namespace forfun::array_concatenation;

    static constexpr std::array const src{
        // clang-format off
           2,    3,    5,    7,   11,   13,   17,   19,
          23,   29,   31,   37,   41,   43,   47,   53,
          59,   61,   67,   71,   73,   79,   83,   89,
          97,  101,  103,  107,  109,  113,  127,  131,
         137,  139,  149,  151,  157,  163,  167,  173,
         179,  181,  191,  193,  197,  199,  211,  223,
         227,  229,  233,  239,  241,  251,  257,  263,
         269,  271,  277,  281,  283,  293,  307,  311,
         313,  317,  331,  337,  347,  349,  353,  359,
         367,  373,  379,  383,  389,  397,  401,  409,
         419,  421,  431,  433,  439,  443,  449,  457,
         461,  463,  467,  479,  487,  491,  499,  503,
         509,  521,  523,  541,  547,  557,  563,  569,
         571,  577,  587,  593,  599,  601,  607,  613,
         617,  619,  631,  641,  643,  647,  653,  659,
         661,  673,  677,  683,  691,  701,  709,  719,
         727,  733,  739,  743,  751,  757,  761,  769,
         773,  787,  797,  809,  811,  821,  823,  827,
         829,  839,  853,  857,  859,  863,  877,  881,
         883,  887,  907,  911,  919,  929,  937,  941,
         947,  953,  967,  971,  977,  983,  991,  997,
        1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
        1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097,
        1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163,
        1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
        1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
        1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321,
        1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423,
        1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459,
        1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
        1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571,
        1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619,
        // clang-format on
    };

    ankerl::nanobench::Bench()

        .title("Concatenation of array")
        .relative(true)

        .run(
            NAMEOF_RAW(functional::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                functional::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(functional_minimal::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                functional_minimal::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(iterator_based::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                iterator_based::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(iterator_based_double::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                iterator_based_double::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(iterator_unfolded::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                iterator_unfolded::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(nested_loops::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                nested_loops::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        .run(
            NAMEOF_RAW(semi_unfolded::concatenate<int, 256>).c_str(),
            []() noexcept {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
                std::array<int, 512> dest /*[[indeterminate]]*/;
                semi_unfolded::concatenate(src, dest);
                ankerl::nanobench::doNotOptimizeAway(dest);
            }
        )

        ;
}
