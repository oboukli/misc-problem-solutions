# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

option(
  FORFUN_FEATURE_BENCHMARKS
  "Enable benchmark drivers"
  OFF
)

option(
  FORFUN_FEATURE_TESTS
  "Enable test drivers"
  OFF
)

option(
  FORFUN_FEATURE_FUZZ_TESTS
  "Enable fuzz test drivers. Requires on Clang Unix-like host"
  OFF
)

option(
  FORFUN_FEATURE_SUPPORT
  "Enable code formatting and support utilities"
  OFF
)

option(
  FORFUN_BUILD_BENCHMARK_TARGETS
  ""
  OFF
)

option(
  FORFUN_BUILD_CUSTOM_TARGETS
  "Build code format and development custom targets"
  OFF
)

option(
  FORFUN_BUILD_FUZZ_TARGETS
  "Requires Clang on Unix-like host"
  OFF
)

option(
  FORFUN_BUILD_TEST_TARGETS
  ""
  OFF
)

option(
  FORFUN_CONFIGURE_INSTALLATION
  ""
  ON
)

option(
  FORFUN_TSAN_BUILD
  ""
  OFF
)

option(
  FORFUN_ASAN_UBSAN_BUILD
  ""
  OFF
)

option(
  FORFUN_CONFIGURE_CODE_COVERAGE
  ""
  OFF
)
