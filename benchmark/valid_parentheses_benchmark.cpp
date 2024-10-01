// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/valid_parentheses.hpp"

TEST_CASE("Valid parentheses benchmarking", "[benchmark][valid_parentheses]")
{
    using namespace forfun::valid_parentheses;

    SECTION("Valid case")
    {
        ankerl::nanobench::Bench()

            .title("Valid parentheses (valid case)")
            .relative(true)

            .run(
                NAMEOF_RAW(deque_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{deque_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(vector_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{vector_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(circuit_breaker::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{circuit_breaker::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(ascii_optimized::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{ascii_optimized::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(vector_based_demi_allocated::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{vector_based_demi_allocated::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(dyn_array_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]]"
                    };

                    bool const r{dyn_array_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            ;
    }

    SECTION("Invalid case")
    {
        ankerl::nanobench::Bench()

            .title("Valid parentheses (invalid case)")
            .relative(true)

            .run(
                NAMEOF_RAW(deque_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{deque_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(vector_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{vector_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(circuit_breaker::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{circuit_breaker::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(ascii_optimized::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{ascii_optimized::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(vector_based_demi_allocated::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{vector_based_demi_allocated::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            .run(
                NAMEOF_RAW(dyn_array_based::is_valid).c_str(),
                []() noexcept {
                    constexpr static std::u8string_view const s{
                        u8"[[[[[[[[[[[[[[[[(((((((((((((((("
                        "{{{{{{{{{{{{{{{{{{{{{{{{(((([[[["
                        "]]]]))))}}}}}}}}}}}}}}}}}}}}}}}}"
                        "))))))))))))))))]]]]]]]]]]]]]]]"
                    };

                    bool const r{dyn_array_based::is_valid(s)};

                    ankerl::nanobench::doNotOptimizeAway(r);
                }
            )

            ;
    }
}
