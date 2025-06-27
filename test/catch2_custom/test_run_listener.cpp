// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iostream>

#include <mimalloc.h>
// Override the C++ new and delete operations.
#include <mimalloc-new-delete.h> // IWYU pragma: keep

#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_test_run_info.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

extern "C" ::mi_output_fun output_handler;

extern "C" auto output_handler(char const* const msg, void* const /*arg*/)
    -> void
{
    std::cout << msg;
}

namespace {

class TestRunListener final : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    TestRunListener(TestRunListener const&) = default;

    TestRunListener(TestRunListener&&) = delete;

    ~TestRunListener() override;

    auto operator=(TestRunListener const&) -> TestRunListener& = default;

    auto operator=(TestRunListener&&) -> TestRunListener& = delete;

    void
    testRunStarting(Catch::TestRunInfo const& /*testRunInfo*/) noexcept override
    {
        ::mi_register_output(&output_handler, nullptr);
    }
};

CATCH_REGISTER_LISTENER(TestRunListener)

TestRunListener::~TestRunListener() = default;

} // namespace
