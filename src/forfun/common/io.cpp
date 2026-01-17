// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/common/io.hpp"

namespace forfun::common::io {

[[nodiscard]] auto null_streambuf::overflow(int_type const chr) noexcept
    -> int_type
{
    return traits_type::not_eof(chr);
}

} // namespace forfun::common::io
