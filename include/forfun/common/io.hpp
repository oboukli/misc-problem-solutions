// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_IO_HPP_
#define FORFUN_COMMON_IO_HPP_

#include <ostream>
#include <streambuf>

namespace forfun::common::io {

// Adapted from https://stackoverflow.com/a/11826666
class oblivion_stream final : public std::ostream {
public:
    oblivion_stream() noexcept;

    virtual auto dummy() noexcept -> void;

private:
    class oblivion_stream_buffer_ final : public std::streambuf {
    protected:
        [[nodiscard]] auto overflow(int_type ch) noexcept -> int_type override;
    };

    oblivion_stream_buffer_ os_buffer_{};
};

} // namespace forfun::common::io

#endif // FORFUN_COMMON_IO_HPP_
