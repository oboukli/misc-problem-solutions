// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include <absl/random/bit_gen_ref.h>

#include "forfun/permutation_in_string.hpp"

namespace {

using NeedleHaystackPair = std::pair<std::string, std::string>;

auto fuzz_permutation_in_string_positive_case(NeedleHaystackPair const& pair)
    -> void
{
    ASSERT_TRUE(
        forfun::permutation_in_string::check_inclusion(pair.first, pair.second)
    );
}

auto fuzz_experimental_permutation_in_string_positive_case(
    NeedleHaystackPair const& pair
) -> void
{
    ASSERT_TRUE(
        forfun::permutation_in_string::experimental::check_inclusion(
            pair.first, pair.second
        )
    );
}

auto fuzz_permutation_in_string_positive_cross_check(
    NeedleHaystackPair const& pair
) -> void
{
    ASSERT_EQ(
        forfun::permutation_in_string::check_inclusion(pair.first, pair.second),
        forfun::permutation_in_string::experimental::check_inclusion(
            pair.first, pair.second
        )
    );
}

auto NonEmptyLowerAlpha() -> ::fuzztest::Domain<std::string>
{
    using ::fuzztest::InRange;
    using ::fuzztest::NonEmpty;
    using ::fuzztest::StringOf;

    return NonEmpty(StringOf(InRange('a', 'z')));
}

auto Needle(std::string const& s, std::size_t const needle_size)
    -> ::fuzztest::Domain<std::string>
{
    using ::fuzztest::Arbitrary;
    using ::fuzztest::FlatMap;
    using ::fuzztest::InRange;
    using ::fuzztest::Just;

    return FlatMap(
        // clang-format off
        [](std::string const& s,
            std::size_t size,
            std::size_t index,
            ::absl::BitGenRef rng)
        // clang-format on
        -> ::fuzztest::Domain<std::string> {
            std::string needle{s.substr(index, size)};
            std::shuffle(std::begin(needle), std::end(needle), rng);

            return Just(needle);
        },
        Just(s),
        Just(needle_size),
        InRange(0UZ, s.size() - needle_size),
        Arbitrary<::absl::BitGenRef>()
    );
}

auto ArbitraryPositiveNeedleHaystackPair()
    -> ::fuzztest::Domain<NeedleHaystackPair>
{
    using ::fuzztest::FlatMap;

    return FlatMap(
        [](std::string const& s) -> ::fuzztest::Domain<NeedleHaystackPair> {
            using ::fuzztest::Just;
            using ::fuzztest::InRange;
            return FlatMap(
                [](std::string const& s, std::size_t const needle_size)
                    -> ::fuzztest::Domain<NeedleHaystackPair> {
                    return FlatMap(
                        [](std::string needle, std::string haystack)
                            -> ::fuzztest::Domain<NeedleHaystackPair> {
                            using ::fuzztest::PairOf;

                            return PairOf(
                                Just(std::move(needle)),
                                Just(std::move(haystack))
                            );
                        },
                        Needle(s, needle_size),
                        Just(s)
                    );
                },
                Just(s),
                InRange(1UZ, s.size())
            );
        },
        NonEmptyLowerAlpha()
    );
}

auto ArbitraryNeedleHaystackPair() -> ::fuzztest::Domain<NeedleHaystackPair>
{
    using ::fuzztest::FlatMap;

    return FlatMap(
        // clang-format off
        [](std::string const& s1,
            std::string const& s2)
        // clang-format on
        -> ::fuzztest::Domain<NeedleHaystackPair> {
            using std::size;
            using ::fuzztest::Just;
            using ::fuzztest::PairOf;

            if (size(s1) < size(s2))
            {
                return PairOf(Just(s1), Just(s2));
            }

            return PairOf(Just(s2), Just(s1));
        },
        NonEmptyLowerAlpha(),
        NonEmptyLowerAlpha()
    );
}

} // namespace

FUZZ_TEST(permutation_in_string, fuzz_permutation_in_string_positive_case)
    .WithDomains(ArbitraryPositiveNeedleHaystackPair());

FUZZ_TEST(
    permutation_in_string, fuzz_experimental_permutation_in_string_positive_case
)
    .WithDomains(ArbitraryPositiveNeedleHaystackPair());

FUZZ_TEST(
    permutation_in_string, fuzz_permutation_in_string_positive_cross_check
)
    .WithDomains(ArbitraryNeedleHaystackPair());
