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
#include <concepts>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

namespace forfun::evaluate_reverse_polish_notation {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif // __clang__

namespace hardened {

// NOLINTBEGIN(performance-unnecessary-value-param)

template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::same_as<std::iter_value_t<Iter>, std::string_view>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const last)
    -> std::pair<int, std::errc>
{
    using calc_type = double;

    if (iter == last) [[unlikely]]
    {
        return {0, std::errc{}};
    }

    std::vector<calc_type> evaluation_stack;
    evaluation_stack.reserve(
        static_cast<decltype(evaluation_stack)::size_type>(last - iter)
    );

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(),
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                iter->data() + iter->size(),
                operand
            )};
            parse_result.ec == std::errc{}
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            && parse_result.ptr == iter->data() + iter->size())
        {
            evaluation_stack.push_back(operand);
        }
        else if (
            (iter->length() != std::string_view::size_type{1})
            || (evaluation_stack.size() < std::vector<int>::size_type{2})
        )
        {
            return {0, std::errc::invalid_argument};
        }
        else
        {
            calc_type const operand_b{evaluation_stack.back()};
            evaluation_stack.pop_back();
            calc_type& accumulator{evaluation_stack.back()};

            switch (iter->front())
            {
            case '+':
                accumulator += operand_b;
                break;

            case '-':
                accumulator -= operand_b;
                break;

            case '*':
                accumulator *= operand_b;
                break;

            case '/':
                if (operand_b == 0.0) [[unlikely]]
                {
                    return {0, std::errc::invalid_argument};
                }

                accumulator = std::trunc(accumulator / operand_b);
                break;

            default:
                return {0, std::errc::invalid_argument};
            }
        }

        ++iter;
    } while (iter != last);

    if (calc_type const res{std::trunc(evaluation_stack.back())};
        (res >= std::numeric_limits<int>::min())
        && (res <= std::numeric_limits<int>::max()))
    {
        return {static_cast<int>(res), std::errc{}};
    }

    return {0, std::errc::argument_out_of_domain};
}

// NOLINTEND(performance-unnecessary-value-param)

} // namespace hardened

namespace unhardened {

// NOLINTBEGIN(performance-unnecessary-value-param)

/// @note All input must be non-empty, valid, and computable.
/// @note Division operands may not be zero; otherwise the behavior is
/// undefined.
/// @note Calculation may overflow without notice or error.
template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::same_as<std::iter_value_t<Iter>, std::string_view>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const last)
    -> std::pair<int, std::errc>
{
    std::vector<int> evaluation_stack;
    evaluation_stack.reserve(
        static_cast<std::vector<int>::size_type>(last - iter)
    );

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(),
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                iter->data() + iter->size(),
                operand
            )};
            parse_result.ec == std::errc{})
        {
            evaluation_stack.push_back(operand);
        }
        else
        {
            int const operand_b{evaluation_stack.back()};
            evaluation_stack.pop_back();
            int& accumulator{evaluation_stack.back()};
            switch (iter->front())
            {
            case '+':
                accumulator += operand_b;
                break;

            case '-':
                accumulator -= operand_b;
                break;

            case '*':
                accumulator *= operand_b;
                break;

            case '/':
                assert(operand_b != 0);

#ifdef __clang_analyzer__
                if (operand_b == 0)
                {
                    __builtin_unreachable();
                }
#endif

#if __has_cpp_attribute(assume)
                [[assume(operand_b != 0)]];
#elifdef __clang__
                __builtin_assume(operand_b != 0);
                [[clang::suppress]]
#elifdef _MSC_VER
                __assume(operand_b != 0);
#endif // __has_cpp_attribute(assume)
                accumulator /= operand_b;
                break;

            default:
                return {0, std::errc::invalid_argument};
            }
        }

        ++iter;
    } while (iter != last);

    return {evaluation_stack.back(), std::errc{}};
}

// NOLINTEND(performance-unnecessary-value-param)

} // namespace unhardened

namespace speed_optimized {

// NOLINTBEGIN(performance-unnecessary-value-param)

/// @note All input must be non-empty, valid, and computable.
/// @note Division operands may not be zero; otherwise the behavior is
/// undefined.
/// @note Calculation may overflow without notice or error.
template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Sentinel, Iter>
    and std::same_as<std::iter_value_t<Iter>, std::string_view>
[[nodiscard]] auto eval_expression(Iter iter, Sentinel const last)
    -> std::pair<int, std::errc>
{
    auto const evaluation_stack{
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        std::make_unique_for_overwrite<int[]>(
            static_cast<std::size_t>(last - iter) + 1UZ
        )
    };

    int* evaluation_stack_top{evaluation_stack.get()};
    *evaluation_stack_top = 0;

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int operand /*[[indeterminate]]*/;
        if (std::from_chars_result const parse_result{std::from_chars(
                iter->data(),
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                iter->data() + iter->size(),
                operand
            )};
            parse_result.ec == std::errc{})
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            ++evaluation_stack_top;
            *evaluation_stack_top = operand;
        }
        else
        {
            int const operand_b{*evaluation_stack_top};

            assert(
                (evaluation_stack_top - evaluation_stack.get())
                >= std::ptrdiff_t{2}
            );
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            --evaluation_stack_top;

            // NOLINTNEXTLINE(clang-analyzer-security.ArrayBound)
            int& accumulator{*evaluation_stack_top};
            switch (iter->front())
            {
            case '+':
                accumulator += operand_b;
                break;

            case '-':
                accumulator -= operand_b;
                break;

            case '*':
                accumulator *= operand_b;
                break;

            case '/':
                assert(operand_b != 0);

#ifdef __clang_analyzer__
                if (operand_b == 0)
                {
                    __builtin_unreachable();
                }
#endif

#if __has_cpp_attribute(assume)
                [[assume(operand_b != 0)]];
#elifdef __clang__
                __builtin_assume(operand_b != 0);
                [[clang::suppress]]
#elifdef _MSC_VER
                __assume(operand_b != 0);
#endif // __has_cpp_attribute(assume)
                accumulator /= operand_b;
                break;

            default:
                return {0, std::errc::invalid_argument};
            }
        }

        ++iter;
    } while (iter != last);

    return {*evaluation_stack_top, std::errc{}};
}

// NOLINTEND(performance-unnecessary-value-param)

} // namespace speed_optimized

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

} // namespace forfun::evaluate_reverse_polish_notation

#endif // FORFUN_EVALUATE_REVERSE_POLISH_NOTATION_HPP_
