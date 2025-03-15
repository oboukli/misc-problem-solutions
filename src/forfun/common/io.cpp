// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/common/io.hpp"

#include <ostream>

namespace forfun::common::io {

oblivion_stream::oblivion_stream() noexcept : std::ostream(&os_buffer_)
{
}

auto oblivion_stream::dummy() noexcept -> void
{
}

[[nodiscard]] auto
oblivion_stream::oblivion_stream_buffer_::overflow(int_type ch) noexcept
    -> int_type
{
    return ch;
}

} // namespace forfun::common::io
