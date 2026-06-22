// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdio>

#include <mimalloc.h>
// Override the C++ new and delete operations.
#include <mimalloc-new-delete.h> // IWYU pragma: keep

#include <catch2/catch_test_run_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

extern "C" ::mi_output_fun output_handler;

extern "C" auto output_handler(char const* const msg, void* const /*arg*/)
    -> void
{
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage-in-libc-call"
#endif // __clang__

    int const res{std::fputs(msg, stdout)};
    if (res == EOF)
    {
        std::perror("Output handler failed");
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
}

namespace {

class TestRunListener final : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    void testRunStarting(
        Catch::TestRunInfo const& /* unused */
    ) noexcept override
    {
        ::mi_register_output(&output_handler, nullptr);
    }
};

CATCH_REGISTER_LISTENER(TestRunListener)

} // namespace
