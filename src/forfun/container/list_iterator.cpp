// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/container/list_iterator.hpp"
#include "forfun/container/list.hpp"

namespace forfun::experimental::container {

[[nodiscard]] auto list::begin() const noexcept -> iterator
{
    return list_iterator(head_);
}

[[nodiscard]] auto list::end() const noexcept -> iterator
{
    return list_iterator{nullptr};
}

} // namespace forfun::experimental::container
