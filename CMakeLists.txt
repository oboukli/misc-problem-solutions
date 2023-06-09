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
  "include/forfun/fizzbuzz.hpp"
  "include/forfun/lru_cache.hpp"
  "include/forfun/palindrome.hpp"
  "include/forfun/palindromic_number.hpp"
  "include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp"
  "include/forfun/sonar.hpp"
  "src/fizzbuzz.cpp"
  "src/lru_cache.cpp"
  "src/palindrome.cpp"
  "src/palindromic_number.cpp"
  "src/project_euler/p0001_multiples_of_3_or_5.cpp"
  "src/sonar.cpp"
)

target_include_directories(
  forfun
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

link_libraries(forfun)

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

link_libraries(forfun_c)

add_executable(
  fizzbuzz
  "test/fizzbuzz.cpp"
)

add_executable(
  lru_cache
  "test/lru_cache.cpp"
)

add_executable(
  palindrome
  "test/palindrome.cpp"
)

add_executable(
  palindrome_c
  "test/palindrome.c"
)

add_executable(
  palindromic_number
  "test/palindromic_number.cpp"
)

add_executable(
  project_euler_p0001_multiples_of_3_or_5
  "test/project_euler/p0001_multiples_of_3_or_5.cpp"
)

add_executable(
  sonar
  "test/sonar.cpp"
)

find_package(Catch2 3 REQUIRED)
add_executable(
  tests
  "test/fizzbuzz_test.cpp"
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

find_package(fmt CONFIG REQUIRED)
find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark
  "benchmark/benchmark.cpp"
  "benchmark/lru_cache_benchmark.cpp"
  "benchmark/palindrome_benchmark.cpp"
)
target_link_libraries(
  benchmark
  PRIVATE Catch2::Catch2WithMain
  PRIVATE fmt::fmt
)
