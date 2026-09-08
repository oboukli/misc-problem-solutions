# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(cmake/Options.cmake)

if(FORFUN_FEATURE_BENCHMARKS)
  set(FORFUN_BUILD_BENCHMARK_TARGETS ON)
  list(APPEND VCPKG_MANIFEST_FEATURES "benchmarks")
endif()

if(FORFUN_FEATURE_FUZZ_TESTS)
  set(FORFUN_BUILD_FUZZ_TARGETS ON)
  list(APPEND VCPKG_MANIFEST_FEATURES "fuzz-tests")
endif()

if(FORFUN_FEATURE_TESTS)
  set(FORFUN_BUILD_TEST_TARGETS ON)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

if(FORFUN_FEATURE_SUPPORT)
  set(FORFUN_BUILD_CUSTOM_TARGETS ON)
endif()
