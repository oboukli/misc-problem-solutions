cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  ForFun
  LANGUAGES CXX
)

add_library(
  forfun
  SHARED
  "include/forfun/fizzbuzz.hpp"
  "include/forfun/lc-lru-cache.hpp"
  "include/forfun/palindrome.hpp"
  "include/forfun/palindromic-number.hpp"
  "include/forfun/project-euler/p0001-multiples-of-3-or-5.hpp"
  "include/forfun/sonar.hpp"
  "src/fizzbuzz.cpp"
  "src/lc-lru-cache.cpp"
  "src/palindrome.cpp"
  "src/palindromic-number.cpp"
  "src/project-euler/p0001-multiples-of-3-or-5.cpp"
  "src/sonar.cpp"
)

target_include_directories (
  forfun
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

link_libraries(forfun)

add_executable(
  "fizzbuzz"
  "test/fizzbuzz.cpp"
)

add_executable(
  "lc-lru-cache"
  "test/lc-lru-cache.cpp"
)

add_executable(
  "palindrome"
  "test/palindrome.cpp"
)

add_executable(
  "palindromic-number"
  "test/palindromic-number.cpp"
)

add_executable(
  "project-euler-p0001-multiples-of-3-or-5"
  "test/project-euler/p0001-multiples-of-3-or-5.cpp"
)

add_executable(
  "sonar"
  "test/sonar.cpp"
)
