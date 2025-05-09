// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
#define FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <catch2/catch_tostring.hpp>
#include <catch2/internal/catch_is_permutation.hpp>
#include <catch2/matchers/catch_matchers.hpp>

namespace forfun::testing::catch2_custom::matchers {

// Disclaimer: Partially AI-assisted code (assisted by GitHub Copilot).
class UnorderedVecOfVecOfStringMatcher
    // clang-format off
    : public Catch::Matchers::MatcherBase<
        std::vector<std::vector<std::string>>> {
    // clang-format on
public:
    explicit UnorderedVecOfVecOfStringMatcher(
        std::vector<std::vector<std::string>> const& expected
    ) :
        expected_{expected}
    {
    }

    [[nodiscard]] auto
    match(std::vector<std::vector<std::string>> const& actual) const
        -> bool override
    {
        if (actual.size() != expected_.size())
        {
            return false;
        }

        auto inner_sorted_expected{expected_};
        auto inner_sorted_actual{actual};

        for (auto& v : inner_sorted_expected)
        {
            std::ranges::sort(v);
        }

        for (auto& v : inner_sorted_actual)
        {
            std::ranges::sort(v);
        }

        return Catch::Detail::is_permutation(
            inner_sorted_expected.cbegin(),
            inner_sorted_expected.cend(),
            inner_sorted_actual.cbegin(),
            inner_sorted_actual.cend(),
            std::equal_to{}
        );
    }

    [[nodiscard]] auto describe() const -> std::string override
    {
        return "unordered elements are " + Catch::Detail::stringify(expected_);
    }

private:
    std::vector<std::vector<std::string>> expected_;
};

// Disclaimer: Partially AI-assisted code (assisted by GitHub Copilot).
inline auto UnorderedVectorOfVectorsEquals(
    std::vector<std::vector<std::string>> const& expected
) -> UnorderedVecOfVecOfStringMatcher
{
    return UnorderedVecOfVecOfStringMatcher{expected};
}

} // namespace forfun::testing::catch2_custom::matchers

#endif // FORFUN_TESTING_CATCH2_CUSTOM_MATCHERS_HPP_
