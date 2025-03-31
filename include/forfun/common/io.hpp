// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_IO_HPP_
#define FORFUN_COMMON_IO_HPP_

#include <streambuf>

namespace forfun::common::io {

class null_streambuf final : public std::streambuf {
public:
    null_streambuf()
    {
        this->setbuf(nullptr, 0); // DevSkim: ignore DS154189
    }

    null_streambuf(null_streambuf const&) = delete;

    null_streambuf(null_streambuf&&) = delete;

    ~null_streambuf() override = default;

    auto operator=(null_streambuf const&) -> null_streambuf& = delete;

    auto operator=(null_streambuf&&) -> null_streambuf& = delete;

protected:
    [[nodiscard]] auto overflow(int_type c) noexcept -> int_type override;
};

} // namespace forfun::common::io

#endif // FORFUN_COMMON_IO_HPP_
