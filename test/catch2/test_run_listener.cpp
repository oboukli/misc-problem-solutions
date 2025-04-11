// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <mimalloc.h>

// Override the C++ new and delete operations.
#include <mimalloc-new-delete.h>

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

namespace {

class TestRunListener final : public Catch::EventListenerBase {
public:
    using Catch::EventListenerBase::EventListenerBase;

    TestRunListener(TestRunListener const&) = default;

    TestRunListener(TestRunListener&&) = delete;

    ~TestRunListener() override;

    auto operator=(TestRunListener const&) -> TestRunListener& = default;

    auto operator=(TestRunListener&&) -> TestRunListener& = delete;

    void
    testRunStarting(Catch::TestRunInfo const& /*testRunInfo*/) noexcept override
    {
        // Ensure mimalloc.dll is loaded on Windows.
        ::mi_version();
    }
};

#ifdef _WIN32
CATCH_REGISTER_LISTENER(TestRunListener)
#endif // _WIN32

TestRunListener::~TestRunListener() = default;

} // namespace
