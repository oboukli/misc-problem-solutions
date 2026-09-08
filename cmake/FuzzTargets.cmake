# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(FetchContent)

FetchContent_Declare(
  google_fuzztest
  GIT_REPOSITORY https://github.com/google/fuzztest.git
  GIT_TAG b73724d4866c22d9b64c152a2d7ac22c7ca94168 # 2026-02-19
)
FetchContent_MakeAvailable(google_fuzztest)

fuzztest_setup_fuzzing_flags()

add_executable(
  fuzzing_driver
)

include(cmake/TargetHelpers.cmake)

forfun_target_config(
  fuzzing_driver
  SOURCES_DIR "fuzz"
  SOURCES
    "encode_and_decode_strings_fuzz.cpp"
    "evaluate_reverse_polish_notation_fuzz.cpp"
    "permutation_in_string_fuzz.cpp"
    "search/binary_search_fuzz.cpp"
    "search/minimum_rotated_element_fuzz.cpp"
    "sorting/bubble_sort_fuzz.cpp"
    "sorting/insertion_sort_fuzz.cpp"
    "sorting/quicksort_fuzz.cpp"
    "squares_sorted_array_fuzz.cpp"
)
target_link_libraries(
  fuzzing_driver
  PRIVATE
    GTest::gmock
    GTest::gtest
)
target_link_libraries(
  fuzzing_driver
  PRIVATE
    forfun_core
)
link_fuzztest(fuzzing_driver)

enable_testing()

include(GoogleTest)

gtest_discover_tests(fuzzing_driver)
