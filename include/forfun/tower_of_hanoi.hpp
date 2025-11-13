// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Tower_of_Hanoi

#ifndef FORFUN_TOWER_OF_HANOI_HPP_
#define FORFUN_TOWER_OF_HANOI_HPP_

#include <concepts>

namespace forfun::tower_of_hanoi::recursive {

template <typename Rod, std::invocable<Rod&, Rod&> Monk>
constexpr auto toh(
    Rod& src, Rod& des, Rod& aux, Monk monk, std::integral auto num_moves
) noexcept(noexcept(monk(src, des))) -> void
{
    if (num_moves == decltype(num_moves){}) [[unlikely]]
    {
        return;
    }

    --num_moves;
    toh(src, aux, des, monk, num_moves);
    monk(src, des);
    toh(aux, des, src, monk, num_moves);
}

} // namespace forfun::tower_of_hanoi::recursive

#endif // FORFUN_TOWER_OF_HANOI_HPP_
