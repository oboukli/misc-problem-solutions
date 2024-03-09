# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_XCODE_XCCONFIG "vendor/XcodeWarnings/XcodeWarnings.xcconfig")

set(
  CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file"
)

project(
  ForFun
  LANGUAGES C CXX
)

add_library(
  forfun
  SHARED
  "include/forfun/common.hpp"
  "include/forfun/contains_duplicate.hpp"
  "include/forfun/factorial.hpp"
  "include/forfun/fibonacci_sequence.hpp"
  "include/forfun/fibonacci.hpp"
  "include/forfun/first_missing_positive.hpp"
  "include/forfun/fizzbuzz.hpp"
  "include/forfun/lru_cache.hpp"
  "include/forfun/move_zeroes.hpp"
  "include/forfun/palindrome.h"
  "include/forfun/palindrome.hpp"
  "include/forfun/palindromic_number.hpp"
  "include/forfun/product_except_self.hpp"
  "include/forfun/sonar.hpp"
  "include/forfun/sub_array_sums.hpp"
  "include/forfun/trie.hpp"
  "include/forfun/two_sum.hpp"
  "src/common.cpp"
  "src/contains_duplicate.cpp"
  "src/factorial.cpp"
  "src/fibonacci_sequence.cpp"
  "src/fibonacci.cpp"
  "src/first_missing_positive.cpp"
  "src/fizzbuzz.cpp"
  "src/lru_cache.cpp"
  "src/move_zeroes.cpp"
  "src/palindrome.c"
  "src/palindrome.cpp"
  "src/palindromic_number.cpp"
  "src/product_except_self.cpp"
  "src/sonar.cpp"
  "src/sub_array_sums.cpp"
  "src/trie.cpp"
  "src/two_sum.cpp"
)
target_include_directories(
  forfun
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

add_library(
  forfun_project_euler
  SHARED
  "include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp"
  "src/project_euler/p0001_multiples_of_3_or_5.cpp"
)
target_include_directories(
  forfun_project_euler
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

add_library(
  forfun_sorting
  SHARED
  "include/forfun/sorting/bubble_sort.hpp"
  "include/forfun/sorting/insertion_sort.hpp"
  "include/forfun/sorting/quicksort.hpp"
  "src/sorting/bubble_sort.cpp"
  "src/sorting/insertion_sort.cpp"
  "src/sorting/quicksort.cpp"
)
target_include_directories(
  forfun_sorting
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

find_package(Catch2 3 REQUIRED)
add_executable(
  tests
  "test/common_test.cpp"
  "test/contains_duplicate_test.cpp"
  "test/factorial_test.cpp"
  "test/fibonacci_sequence_test.cpp"
  "test/fibonacci_test.cpp"
  "test/first_missing_positive_test.cpp"
  "test/fizzbuzz_test.cpp"
  "test/lru_cache_test.cpp"
  "test/move_zeroes_test.cpp"
  "test/palindrome_test.cpp"
  "test/palindromic_number_test.cpp"
  "test/product_except_self_test.cpp"
  "test/project_euler/p0001_multiples_of_3_or_5_test.cpp"
  "test/sonar_test.cpp"
  "test/sorting/bubble_sort_test.cpp"
  "test/sorting/insertion_sort_test.cpp"
  "test/sorting/quicksort_test.cpp"
  "test/sub_array_sums_test.cpp"
  "test/trie_test.cpp"
  "test/two_sum_test.cpp"
)
target_link_libraries(
  tests
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  tests
  PRIVATE forfun
  PRIVATE forfun_sorting
)
include(CTest)
include(Catch)
catch_discover_tests(tests)

find_package(fmt CONFIG REQUIRED)
find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark
  "benchmark/benchmark.cpp"
  "benchmark/contains_duplicate_benchmark.cpp"
  "benchmark/factorial_benchmark.cpp"
  "benchmark/fibonacci_benchmark.cpp"
  "benchmark/fibonacci_sequence_benchmark.cpp"
  "benchmark/first_missing_positive_benchmark.cpp"
  "benchmark/lru_cache_benchmark.cpp"
  "benchmark/move_zeroes_benchmark.cpp"
  "benchmark/palindrome_benchmark.cpp"
  "benchmark/palindromic_number_benchmark.cpp"
  "benchmark/product_except_self_benchmark.cpp"
  "benchmark/sonar_benchmark.cpp"
  "benchmark/sorting/bubble_sort_benchmark.cpp"
  "benchmark/sorting/insertion_sort_benchmark.cpp"
  "benchmark/sorting/quicksort_benchmark.cpp"
  "benchmark/sub_array_sums_benchmark.cpp"
)
target_link_libraries(
  benchmark
  PRIVATE Catch2::Catch2WithMain
  PRIVATE fmt::fmt
)
target_link_libraries(
  benchmark
  PRIVATE forfun
)
