# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
  CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file"
)

project(
  ForFun
  LANGUAGES C CXX
)

add_library(
  forfun
  SHARED
  "include/forfun/first_missing_positive.hpp"
  "include/forfun/fizzbuzz.hpp"
  "include/forfun/lru_cache.hpp"
  "include/forfun/palindrome.hpp"
  "include/forfun/palindromic_number.hpp"
  "include/forfun/sonar.hpp"
  "src/first_missing_positive.cpp"
  "src/fizzbuzz.cpp"
  "src/lru_cache.cpp"
  "src/palindrome.cpp"
  "src/palindromic_number.cpp"
  "src/sonar.cpp"
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
  "include/forfun/sorting/insertion.hpp"
  "include/forfun/sorting/quicksort.hpp"
  "src/sorting/insertion.cpp"
  "src/sorting/quicksort.cpp"
)
target_include_directories(
  forfun_sorting
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

add_library(
  forfun_c
  SHARED
  "include/forfun/palindrome.h"
  "src/palindrome.c"
)
target_include_directories(
  forfun_c
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

add_executable(
  lru_cache
  "test/lru_cache.cpp"
)
target_link_libraries(
  lru_cache
  PRIVATE forfun
)

add_executable(
  palindrome
  "test/palindrome.cpp"
)
target_link_libraries(
  palindrome
  PRIVATE forfun
)

add_executable(
  palindrome_c
  "test/palindrome.c"
)
target_link_libraries(
  palindrome_c
  PRIVATE forfun_c
)

add_executable(
  palindromic_number
  "test/palindromic_number.cpp"
)
target_link_libraries(
  palindromic_number
  PRIVATE forfun
)

add_executable(
  project_euler_p0001_multiples_of_3_or_5
  "test/project_euler/p0001_multiples_of_3_or_5.cpp"
)
target_link_libraries(
  project_euler_p0001_multiples_of_3_or_5
  PRIVATE forfun_project_euler
)

add_executable(
  sonar
  "test/sonar.cpp"
)
target_link_libraries(
  sonar
  PRIVATE forfun
)

find_package(Catch2 3 REQUIRED)
add_executable(
  tests
  "test/first_missing_positive_test.cpp"
  "test/fizzbuzz_test.cpp"
  "test/sorting/insertion_test.cpp"
  "test/sorting/quicksort_test.cpp"
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

find_package(fmt CONFIG REQUIRED)
find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark
  "benchmark/benchmark.cpp"
  "benchmark/first_missing_positive_benchmark.cpp"
  "benchmark/lru_cache_benchmark.cpp"
  "benchmark/palindrome_benchmark.cpp"
)
target_link_libraries(
  benchmark
  PRIVATE Catch2::Catch2WithMain
  PRIVATE fmt::fmt
)
target_link_libraries(
  benchmark
  PRIVATE forfun
  PRIVATE forfun_c
)
