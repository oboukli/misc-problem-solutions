// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/evaluate-reverse-polish-notation/

#ifndef FORFUN_EVALUATE_REVERSE_POLISH_NOTATION_HPP_
#define FORFUN_EVALUATE_REVERSE_POLISH_NOTATION_HPP_

#include <cassert>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

namespace forfun::evaluate_reverse_polish_notation {

namespace hardened {

template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const end)
    -> std::pair<int, std::errc>
{
    using calc_type = double;

    if (iter == end) [[unlikely]]
    {
        return {0, std::errc{}};
    }

    std::vector<calc_type> evaluation_stack;
    evaluation_stack.reserve(
        static_cast<decltype(evaluation_stack)::size_type>(end - iter)
    );

    for (; iter != end; ++iter)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(), iter->data() + iter->size(), operand
            )};
            parse_result.ec == std::errc{}
            && parse_result.ptr == iter->data() + iter->size())
        {
            evaluation_stack.push_back(operand);

            continue;
        }

        if ((iter->length() == std::string_view::size_type{1})
            && (evaluation_stack.size() >= std::vector<int>::size_type{2}))
        {
            calc_type const operand_2{evaluation_stack.back()};
            evaluation_stack.pop_back();
            calc_type& accumulator{evaluation_stack.back()};

            switch (iter->front())
            {
            case '+':
                accumulator += operand_2;
                continue;
            case '-':
                accumulator -= operand_2;
                continue;
            case '*':
                accumulator *= operand_2;
                continue;
            case '/':
                if (operand_2 == 0.0) [[unlikely]]
                {
                    break;
                }
                accumulator = std::trunc(accumulator / operand_2);
                continue;
            default:
                break;
            }
        }

        return {0, std::errc::invalid_argument};
    }

    // clang-format off
    if (calc_type const intermediate{std::trunc(evaluation_stack.back())};
        ((intermediate >= std::numeric_limits<int>::min())
        && (intermediate <= std::numeric_limits<int>::max())))
    // clang-format on
    {
        return {static_cast<int>(intermediate), std::errc{}};
    }

    return {0, std::errc::invalid_argument};
}

} // namespace hardened

namespace unhardened {

/// @note Calculation may overflow without notice or error.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const end)
    -> std::pair<int, std::errc>
{
    if (iter == end) [[unlikely]]
    {
        return {0, std::errc{}};
    }

    std::vector<int> evaluation_stack;
    evaluation_stack.reserve(
        static_cast<std::vector<int>::size_type>(end - iter)
    );

    for (; iter != end; ++iter)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(), iter->data() + iter->size(), operand
            )};
            parse_result.ec == std::errc{})
        {
            evaluation_stack.push_back(operand);

            continue;
        }

        int const operand_2{evaluation_stack.back()};
        evaluation_stack.pop_back();
        int& accumulator{evaluation_stack.back()};

        switch (iter->front())
        {
        case '+':
            accumulator += operand_2;
            continue;
        case '-':
            accumulator -= operand_2;
            continue;
        case '*':
            accumulator *= operand_2;
            continue;
        case '/':
            assert(operand_2 != 0);
#if __has_cpp_attribute(assume)
            [[assume(operand_2 != 0)]];
#endif // __has_cpp_attribute(assume)
            accumulator /= operand_2;
            continue;
        default:
            break;
        }

        return {0, std::errc::invalid_argument};
    }

    return {evaluation_stack.back(), std::errc{}};
}

} // namespace unhardened

namespace speed_optimized {

/// @note Calculation may overflow without notice or error.
template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const end)
    -> std::pair<int, std::errc>
{
    std::unique_ptr const evaluation_stack{
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
        std::make_unique_for_overwrite<int[]>(
            static_cast<std::size_t>(end - iter) + 1U
        )
    };

    int* evaluation_stack_top{evaluation_stack.get()};
    *evaluation_stack_top = 0;

    for (; iter != end; ++iter)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(), iter->data() + iter->size(), operand
            )};
            parse_result.ec == std::errc{})
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            ++evaluation_stack_top;
            *evaluation_stack_top = operand;

            continue;
        }

        int const operand_2{*evaluation_stack_top};

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        --evaluation_stack_top;
        int& accumulator{*evaluation_stack_top};

        switch (iter->front())
        {
        case '+':
            accumulator += operand_2;
            continue;
        case '-':
            accumulator -= operand_2;
            continue;
        case '*':
            accumulator *= operand_2;
            continue;
        case '/':
            assert(operand_2 != 0);
#if __has_cpp_attribute(assume)
            [[assume(operand_2 != 0)]];
#endif // __has_cpp_attribute(assume)
            accumulator /= operand_2;
            continue;
        default:
            break;
        }

        return {0, std::errc::invalid_argument};
    }

    return {*evaluation_stack_top, std::errc{}};
}

} // namespace speed_optimized

} // namespace forfun::evaluate_reverse_polish_notation

#endif // FORFUN_EVALUATE_REVERSE_POLISH_NOTATION_HPP_
