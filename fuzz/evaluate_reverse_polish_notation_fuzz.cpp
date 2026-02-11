// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gmock/gmock.h>

#include "forfun/evaluate_reverse_polish_notation.hpp"

namespace {

using OperandOperationPair = std::pair<int, char>;
using OperandOperationStringPair = std::pair<std::string, std::string>;

auto fuzz_hardened_eval_expression(std::vector<std::string> const& tokens)
    -> void
{
    [[maybe_unused]] auto const [actual_result, actual_error]{
        forfun::evaluate_reverse_polish_notation::hardened::eval_expression(
            tokens.cbegin(), tokens.cend()
        )
    };

    EXPECT_THAT(
        actual_error, ::testing::AnyOf(std::errc{}, std::errc::invalid_argument)
    );
}

auto ArbitraryOperation() -> ::fuzztest::Domain<char>
{
    return ::fuzztest::ElementOf<char>({'+', '-', '*', '/'});
}

auto ArbitraryOperand() -> ::fuzztest::Domain<std::int64_t>
{
    return ::fuzztest::Arbitrary<std::int64_t>();
}

auto ArbitraryOperandAndOperation() -> ::fuzztest::Domain<OperandOperationPair>
{
    return ::fuzztest::Map(
        [](int operand, char operation) -> OperandOperationPair {
            OperandOperationPair p{std::make_pair(operand, operation)};
            return p;
        },
        ArbitraryOperand(),
        ArbitraryOperation()
    );
}

auto ArbitraryOperandAndOperatorStringPair()
    -> ::fuzztest::Domain<OperandOperationStringPair>
{
    return ::fuzztest::Map(
        [](OperandOperationPair const& p) -> OperandOperationStringPair {
            OperandOperationStringPair sp{
                std::make_pair(std::to_string(p.first), std::string{p.second})
            };
            return sp;
        },
        ArbitraryOperandAndOperation()
    );
}

auto ArbitraryTokens() -> ::fuzztest::Domain<std::vector<std::string>>
{
    return ::fuzztest::FlatMap(
        [](
            // clang-format off
            std::vector<OperandOperationStringPair>&& vec,
            int first_operand
            // clang-format on
        ) -> ::fuzztest::Domain<std::vector<std::string>> {
            std::vector<OperandOperationStringPair> vec_{std::move(vec)};
            std::vector<std::string> res;
            res.push_back(std::move(std::to_string(first_operand)));
            for (auto&& [operand, operation] : vec_)
            {
                res.push_back(std::move(operand));
                res.push_back(std::move(operation));
            }
            return ::fuzztest::Just(res);
        },
        ::fuzztest::VectorOf(ArbitraryOperandAndOperatorStringPair()),
        ArbitraryOperand()
    );
}

} // namespace

FUZZ_TEST(evaluate_reverse_polish_notation, fuzz_hardened_eval_expression)
    .WithDomains(ArbitraryTokens());
