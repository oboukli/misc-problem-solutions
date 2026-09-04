// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_TYPE_TRAITS_HPP_
#define FORFUN_COMMON_TYPE_TRAITS_HPP_

#include <type_traits>
#include <utility>

namespace forfun::common::type_traits {

template <typename S, typename R>
using conditional_const_t = std::conditional_t<
    std::is_const_v<std::remove_reference_t<S>>,
    std::add_const_t<R>,
    R>;

template <typename S, typename R>
using forward_like_t = decltype(std::forward_like<S>(std::declval<R>()));

template <typename S, typename ConstType, typename MutableType>
using if_const_t = std::conditional_t<
    std::is_const_v<std::remove_reference_t<S>>,
    ConstType,
    MutableType>;

template <typename S, typename R>
using reference_conditional_const_t = std::conditional_t<
    std::is_const_v<std::remove_reference_t<S>>,
    std::add_lvalue_reference_t<std::add_const_t<R>>,
    std::add_lvalue_reference_t<R>>;

template <typename T, typename... Ts>
constexpr bool const type_is_one_of_v
    = std::disjunction_v<std::is_same<T, Ts>...>;

} // namespace forfun::common::type_traits

#endif // FORFUN_COMMON_TYPE_TRAITS_HPP_
