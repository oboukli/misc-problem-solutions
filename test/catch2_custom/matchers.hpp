// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
#define FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>

#include <catch2/catch_tostring.hpp>
#include <catch2/internal/catch_is_permutation.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

namespace forfun::testing::catch2_custom::matchers {

template <typename TargetRangeLike, typename Equality>
class UnorderedNestedRangeEqualsMatcher final
    : public Catch::Matchers::MatcherGenericBase {
    using Range_ = std::remove_cvref_t<TargetRangeLike>;

public:
    explicit constexpr UnorderedNestedRangeEqualsMatcher(
        auto&& expected, auto&& pred
    ) noexcept :
        expected_{std::forward<TargetRangeLike>(expected)},
        equal_to_{std::forward<Equality>(pred)}
    {
    }

    [[nodiscard]] auto match(auto&& actual) const -> bool
    {
        if (actual.size() != expected_.size())
        {
            return false;
        }

        Range_ inner_sorted_expected{std::forward<TargetRangeLike>(expected_)};
        Range_ inner_sorted_actual{std::forward<TargetRangeLike>(actual)};

        for (auto& v : inner_sorted_expected)
        {
            std::ranges::sort(v);
        }

        for (auto& v : inner_sorted_actual)
        {
            std::ranges::sort(v);
        }

        using std::cbegin;
        using std::cend;

        return Catch::Detail::is_permutation(
            cbegin(inner_sorted_expected),
            cend(inner_sorted_expected),
            cbegin(inner_sorted_actual),
            cend(inner_sorted_actual),
            equal_to_
        );
    }

    [[nodiscard]] auto describe() const -> std::string override
    {
        return "unordered elements are " + Catch::Detail::stringify(expected_);
    }

private:
    Range_ expected_;
    Equality equal_to_;
};

template <
    typename RangeOfRange,
    typename Equality = decltype(std::equal_to<>{})>
constexpr auto UnorderedNestedRangeEquals(
    RangeOfRange&& expected, Equality&& predicate = std::equal_to<>{}
) -> UnorderedNestedRangeEqualsMatcher<RangeOfRange, Equality>
{
    return UnorderedNestedRangeEqualsMatcher<RangeOfRange, Equality>{
        std::forward<RangeOfRange>(expected), std::forward<Equality>(predicate)
    };
}

} // namespace forfun::testing::catch2_custom::matchers

#endif // FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
