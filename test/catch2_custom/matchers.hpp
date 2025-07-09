// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
#define FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_

#include <algorithm>
#include <format>
#include <functional>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>

#include <catch2/catch_tostring.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

namespace forfun::testing::catch2_custom::matchers {

template <
    typename TargetRangeOfRangeLike,
    typename OuterEquality,
    typename InnerLess>
class UnorderedNestedRangeEqualsMatcher final
    : public Catch::Matchers::MatcherGenericBase {
public:
    explicit constexpr UnorderedNestedRangeEqualsMatcher(
        auto&& expected, auto&& outer_equal_to, auto&& inner_less
    ) :
        expected_{std::forward<TargetRangeOfRangeLike>(expected)},
        outer_equal_to_{std::forward<OuterEquality>(outer_equal_to)},
        inner_less_{std::forward<InnerLess>(inner_less)},
        description_{std::format(
            "unordered elements are {}", Catch::Detail::stringify(expected_)
        )}
    {
        using std::ranges::sort;

        for (auto& v : expected_)
        {
            sort(v, inner_less_);
        }
    }

    template <typename RangeOfRange>
    [[nodiscard]] auto match(RangeOfRange&& actual) const -> bool
    {
        using std::size;

        if (size(actual) != size(expected_))
        {
            return false;
        }

        using std::ranges::sort;

        auto semi_sorted_actual{std::forward<RangeOfRange>(actual)};

        for (auto& v : semi_sorted_actual)
        {
            sort(v, inner_less_);
        }

        using std::cbegin;
        using std::cend;

        return std::is_permutation(
            cbegin(expected_),
            cend(expected_),
            cbegin(semi_sorted_actual),
            cend(semi_sorted_actual),
            // clang-format off
            [equal_to = outer_equal_to_]
            // clang-format on
            (auto const& a, auto const& b) noexcept -> bool {
                return (size(a) == size(b))
                    && std::equal(cbegin(a), cend(a), cbegin(b), equal_to);
            }
        );
    }

    [[nodiscard]] auto describe() const -> std::string override
    {
        return description_;
    }

private:
    std::remove_cvref_t<TargetRangeOfRangeLike> expected_;
    std::remove_cvref_t<OuterEquality> outer_equal_to_;
    std::remove_cvref_t<InnerLess> inner_less_;
    std::string description_;
};

template <
    typename RangeOfRange,
    typename OuterEquality = std::equal_to<>,
    typename InnerLess = std::less<>>
constexpr auto UnorderedNestedRangeEquals(
    RangeOfRange&& expected,
    OuterEquality&& outer_equal_to = std::equal_to{},
    InnerLess&& inner_less = std::less{}
) -> UnorderedNestedRangeEqualsMatcher<RangeOfRange, OuterEquality, InnerLess>
{
    return UnorderedNestedRangeEqualsMatcher<
        RangeOfRange,
        OuterEquality,
        InnerLess>{
        std::forward<RangeOfRange>(expected),
        std::forward<OuterEquality>(outer_equal_to),
        std::forward<InnerLess>(inner_less)
    };
}

} // namespace forfun::testing::catch2_custom::matchers

#endif // FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
