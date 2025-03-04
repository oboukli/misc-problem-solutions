# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.27)

project(
  ForFun
)

include(cmake/CompileOptions.cmake)

add_library(
  forfun
  SHARED
)
set_target_properties(forfun PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun
  PUBLIC
  "include/"
)
target_sources(
  forfun
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun/add_two_numbers.hpp"
  "include/forfun/array_concatenation.hpp"
  "include/forfun/best_time_to_buy_and_sell_stock.hpp"
  "include/forfun/contains_duplicate.hpp"
  "include/forfun/encode_and_decode_strings.hpp"
  "include/forfun/evaluate_reverse_polish_notation.hpp"
  "include/forfun/factorial.hpp"
  "include/forfun/fibonacci_sequence.hpp"
  "include/forfun/fibonacci.hpp"
  "include/forfun/first_missing_positive.hpp"
  "include/forfun/fizzbuzz.hpp"
  "include/forfun/gcd.hpp"
  "include/forfun/house_robber.hpp"
  "include/forfun/last_stone_weight.hpp"
  "include/forfun/longest_consecutive_sequence.hpp"
  "include/forfun/lru_cache.hpp"
  "include/forfun/majority_element.hpp"
  "include/forfun/maximum_subarray.hpp"
  "include/forfun/meeting_rooms.hpp"
  "include/forfun/move_zeroes.hpp"
  "include/forfun/palindrome.hpp"
  "include/forfun/palindromic_number.hpp"
  "include/forfun/primality.hpp"
  "include/forfun/product_except_self.hpp"
  "include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp"
  "include/forfun/set_matrix_zeroes.hpp"
  "include/forfun/sonar.hpp"
  "include/forfun/sub_array_sums.hpp"
  "include/forfun/top_k_frequent_elements.hpp"
  "include/forfun/tower_of_hanoi.hpp"
  "include/forfun/trie.hpp"
  "include/forfun/two_sum.hpp"
  "include/forfun/valid_anagram.hpp"
  "include/forfun/valid_parentheses.hpp"
  "include/forfun/valid_sudoku.hpp"
)
target_sources(
  forfun
  PRIVATE
  "src/forfun/add_two_numbers.cpp"
  "src/forfun/array_concatenation.cpp"
  "src/forfun/best_time_to_buy_and_sell_stock.cpp"
  "src/forfun/contains_duplicate.cpp"
  "src/forfun/encode_and_decode_strings.cpp"
  "src/forfun/evaluate_reverse_polish_notation.cpp"
  "src/forfun/factorial.cpp"
  "src/forfun/fibonacci_sequence.cpp"
  "src/forfun/fibonacci.cpp"
  "src/forfun/first_missing_positive.cpp"
  "src/forfun/fizzbuzz.cpp"
  "src/forfun/gcd.cpp"
  "src/forfun/house_robber.cpp"
  "src/forfun/last_stone_weight.cpp"
  "src/forfun/longest_consecutive_sequence.cpp"
  "src/forfun/lru_cache.cpp"
  "src/forfun/majority_element.cpp"
  "src/forfun/maximum_subarray.cpp"
  "src/forfun/meeting_rooms.cpp"
  "src/forfun/move_zeroes.cpp"
  "src/forfun/palindrome.cpp"
  "src/forfun/palindromic_number.cpp"
  "src/forfun/primality.cpp"
  "src/forfun/product_except_self.cpp"
  "src/forfun/project_euler/p0001_multiples_of_3_or_5.cpp"
  "src/forfun/set_matrix_zeroes.cpp"
  "src/forfun/sonar.cpp"
  "src/forfun/sub_array_sums.cpp"
  "src/forfun/top_k_frequent_elements.cpp"
  "src/forfun/tower_of_hanoi.cpp"
  "src/forfun/trie.cpp"
  "src/forfun/two_sum.cpp"
  "src/forfun/valid_anagram.cpp"
  "src/forfun/valid_parentheses.cpp"
  "src/forfun/valid_sudoku.cpp"
)
get_target_property(forfun_sources forfun SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun/"
  PREFIX "Source files"
  FILES ${forfun_sources}
)
get_target_property(forfun_headers forfun HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun/"
  PREFIX "Header files"
  FILES ${forfun_headers}
)
forfun_common_target_compile_options(forfun)

add_library(
  forfun_common
  SHARED
)
set_target_properties(forfun_common PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun_common PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun_common PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_common
  PUBLIC
  "include/"
)
target_sources(
  forfun_common
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun/common/concepts.hpp"
  "include/forfun/common/io.hpp"
)
target_sources(
  forfun_common
  PRIVATE
  "src/forfun/common/concepts.cpp"
  "src/forfun/common/io.cpp"
)
get_target_property(forfun_common_headers forfun_common HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun/common/"
  PREFIX "Header files"
  FILES ${forfun_common_headers}
)
get_target_property(forfun_common_sources forfun_common SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun/common/"
  PREFIX "Source files"
  FILES ${forfun_common_sources}
)
forfun_common_target_compile_options(forfun_common)

add_library(
  forfun_graph
  SHARED
)
set_target_properties(forfun_graph PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun_graph PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun_graph PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_graph
  PUBLIC
  "include/"
)
target_sources(
  forfun_graph
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun/graph/balanced_binary_tree.hpp"
  "include/forfun/graph/binary_tree_node.hpp"
  "include/forfun/graph/breadth_first_search.hpp"
  "include/forfun/graph/depth_first_search.hpp"
  "include/forfun/graph/subsets.hpp"
  "include/forfun/graph/vertex.hpp"
)
target_sources(
  forfun_graph
  PRIVATE
  "src/forfun/graph/balanced_binary_tree.cpp"
  "src/forfun/graph/binary_tree_node.cpp"
  "src/forfun/graph/breadth_first_search.cpp"
  "src/forfun/graph/depth_first_search.cpp"
  "src/forfun/graph/subsets.cpp"
  "src/forfun/graph/vertex.cpp"
)
get_target_property(forfun_graph_headers forfun_graph HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun/graph/"
  PREFIX "Header files"
  FILES ${forfun_graph_headers}
)
get_target_property(forfun_graph_sources forfun_graph SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun/graph/"
  PREFIX "Source files"
  FILES ${forfun_graph_sources}
)
forfun_common_target_compile_options(forfun_graph)

add_library(
  forfun_search
  SHARED
)
set_target_properties(forfun_search PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun_search PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun_search PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_search
  PUBLIC
  "include/"
)
target_sources(
  forfun_search
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun/search/binary_search.hpp"
)
target_sources(
  forfun_search
  PRIVATE
  "src/forfun/search/binary_search.cpp"
)
get_target_property(forfun_search_headers forfun_search HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun/search/"
  PREFIX "Header files"
  FILES ${forfun_search_headers}
)
get_target_property(forfun_search_sources forfun_search SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun/search/"
  PREFIX "Source files"
  FILES ${forfun_search_sources}
)
forfun_common_target_compile_options(forfun_search)

add_library(
  forfun_sorting
  SHARED
  "include/forfun/sorting/bubble_sort.hpp"
  "include/forfun/sorting/insertion_sort.hpp"
  "include/forfun/sorting/quicksort.hpp"
  "src/forfun/sorting/bubble_sort.cpp"
  "src/forfun/sorting/insertion_sort.cpp"
  "src/forfun/sorting/quicksort.cpp"
)
set_target_properties(forfun_sorting PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun_sorting PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun_sorting PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_sorting
  PUBLIC
  "include/"
)
forfun_common_target_compile_options(forfun_sorting)

add_library(
  forfun_c
  SHARED
)
set_target_properties(forfun_c PROPERTIES C_EXTENSIONS OFF)
set_target_properties(forfun_c PROPERTIES C_STANDARD 90)
set_target_properties(forfun_c PROPERTIES C_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_c
  PUBLIC
  "include/"
)
target_sources(
  forfun_c
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun_c/palindrome.h"
)
target_sources(
  forfun_c
  PRIVATE
  "src/forfun_c/palindrome.c"
)
get_target_property(forfun_c_sources forfun_c SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun_c/"
  PREFIX "Source files"
  FILES ${forfun_c_sources}
)
get_target_property(forfun_c_headers forfun_c HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun_c/"
  PREFIX "Header files"
  FILES ${forfun_c_headers}
)
forfun_common_target_compile_options(forfun_c)

add_library(
  forfun_c_experimental
  SHARED
)
set_target_properties(forfun_c_experimental PROPERTIES C_EXTENSIONS OFF)
set_target_properties(forfun_c_experimental PROPERTIES C_STANDARD 90)
set_target_properties(forfun_c_experimental PROPERTIES C_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_c_experimental
  PUBLIC
  "include/"
)
target_sources(
  forfun_c_experimental
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun_c/add_two_numbers.h"
  "include/forfun_c/container/forward_list.h"
)
target_sources(
  forfun_c_experimental
  PRIVATE
  "src/forfun_c/add_two_numbers.c"
  "src/forfun_c/container/forward_list.c"
)
get_target_property(forfun_c_experimental_sources forfun_c_experimental SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun_c/"
  PREFIX "Source files"
  FILES ${forfun_c_experimental_sources}
)
get_target_property(forfun_c_experimental_headers forfun_c_experimental HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun_c/"
  PREFIX "Header files"
  FILES ${forfun_c_experimental_headers}
)
forfun_common_target_compile_options(forfun_c_experimental)

find_package(Microsoft.GSL CONFIG REQUIRED)
add_library(
  forfun_experimental
  SHARED
)
set_target_properties(forfun_experimental PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(forfun_experimental PROPERTIES CXX_STANDARD 23)
set_target_properties(forfun_experimental PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(
  forfun_experimental
  PUBLIC
  "include/"
)
target_sources(
  forfun_experimental
  PUBLIC
  FILE_SET HEADERS
  FILES
  "include/forfun/container/forward_list.hpp"
  "include/forfun/container/internal/list_const_iterator.hpp"
  "include/forfun/container/internal/list_iterator_helper.hpp"
  "include/forfun/container/internal/list_iterator.hpp"
  "include/forfun/container/internal/list_node.hpp"
  "include/forfun/container/list.hpp"
)
target_sources(
  forfun_experimental
  PRIVATE
  "src/forfun/container/forward_list.cpp"
  "src/forfun/container/internal/list_const_iterator.cpp"
  "src/forfun/container/internal/list_iterator_helper.cpp"
  "src/forfun/container/internal/list_iterator.cpp"
  "src/forfun/container/internal/list_node.cpp"
  "src/forfun/container/list.cpp"
)
get_target_property(forfun_experimental_sources forfun_experimental SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/forfun/"
  PREFIX "Source files"
  FILES ${forfun_experimental_sources}
)
get_target_property(forfun_experimental_headers forfun_experimental HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/forfun/"
  PREFIX "Header files"
  FILES ${forfun_experimental_headers}
)
target_link_libraries(
  forfun_experimental
  PRIVATE Microsoft.GSL::GSL
)
forfun_common_target_compile_options(forfun_experimental)

find_package(Catch2 3 REQUIRED)
add_executable(
  test_driver
)
set_target_properties(test_driver PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(test_driver PROPERTIES CXX_STANDARD 23)
set_target_properties(test_driver PROPERTIES CXX_STANDARD_REQUIRED ON)
target_sources(
  test_driver
  PRIVATE
  "test/add_two_numbers_test.cpp"
  "test/array_concatenation_test.cpp"
  "test/best_time_to_buy_and_sell_stock_test.cpp"
  "test/common/io_test.cpp"
  "test/contains_duplicate_test.cpp"
  "test/encode_and_decode_strings_test.cpp"
  "test/evaluate_reverse_polish_notation_test.cpp"
  "test/factorial_test.cpp"
  "test/fibonacci_sequence_test.cpp"
  "test/fibonacci_test.cpp"
  "test/first_missing_positive_test.cpp"
  "test/fizzbuzz_test.cpp"
  "test/gcd_test.cpp"
  "test/house_robber_test.cpp"
  "test/graph/balanced_binary_tree_test.cpp"
  "test/graph/binary_tree_node_test.cpp"
  "test/graph/breadth_first_search_test.cpp"
  "test/graph/depth_first_search_test.cpp"
  "test/graph/subsets_test.cpp"
  "test/graph/vertex_test.cpp"
  "test/last_stone_weight_test.cpp"
  "test/longest_consecutive_sequence_test.cpp"
  "test/lru_cache_test.cpp"
  "test/majority_element_test.cpp"
  "test/maximum_subarray_test.cpp"
  "test/meeting_rooms_test.cpp"
  "test/move_zeroes_test.cpp"
  "test/palindrome_test.cpp"
  "test/palindromic_number_test.cpp"
  "test/primality_test.cpp"
  "test/product_except_self_test.cpp"
  "test/project_euler/p0001_multiples_of_3_or_5_test.cpp"
  "test/search/binary_search_test.cpp"
  "test/set_matrix_zeroes_test.cpp"
  "test/sonar_test.cpp"
  "test/sorting/bubble_sort_test.cpp"
  "test/sorting/insertion_sort_test.cpp"
  "test/sorting/quicksort_test.cpp"
  "test/sub_array_sums_test.cpp"
  "test/top_k_frequent_elements_test.cpp"
  "test/tower_of_hanoi_test.cpp"
  "test/trie_test.cpp"
  "test/two_sum_test.cpp"
  "test/valid_anagram_test.cpp"
  "test/valid_parentheses_test.cpp"
  "test/valid_sudoku_test.cpp"
)
get_target_property(forfun_tests test_driver SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${forfun_tests}
)
target_link_libraries(
  test_driver
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  test_driver
  PRIVATE forfun
  PRIVATE forfun_c
  PRIVATE forfun_common
  PRIVATE forfun_graph
  PRIVATE forfun_search
  PRIVATE forfun_sorting
)
forfun_common_target_compile_options(test_driver)

add_executable(
  test_driver_experimental
)
set_target_properties(test_driver_experimental PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(test_driver_experimental PROPERTIES CXX_STANDARD 23)
set_target_properties(test_driver_experimental PROPERTIES CXX_STANDARD_REQUIRED ON)
target_sources(
  test_driver_experimental
  PRIVATE
  "test/add_two_numbers_c_test.cpp"
  "test/container/forward_list_test.cpp"
  "test/container/internal/list_const_iterator_test.cpp"
  "test/container/internal/list_iterator_test.cpp"
  "test/container/list_test.cpp"
)
get_target_property(forfun_experimental_tests test_driver_experimental SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${forfun_experimental_tests}
)
target_link_libraries(
  test_driver_experimental
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  test_driver_experimental
  PRIVATE forfun_c_experimental
  PRIVATE forfun_experimental
)
forfun_common_target_compile_options(test_driver_experimental)

include(CTest)
include(Catch)
catch_discover_tests(test_driver)
catch_discover_tests(test_driver_experimental)

find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark_driver
)
set_target_properties(benchmark_driver PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(benchmark_driver PROPERTIES CXX_STANDARD 23)
set_target_properties(benchmark_driver PROPERTIES CXX_STANDARD_REQUIRED ON)
target_sources(
  benchmark_driver
  PRIVATE
  "benchmark/array_concatenation_benchmark.cpp"
  "benchmark/benchmark.cpp"
  "benchmark/best_time_to_buy_and_sell_stock_benchmark.cpp"
  "benchmark/contains_duplicate_benchmark.cpp"
  "benchmark/evaluate_reverse_polish_notation_benchmark.cpp"
  "benchmark/factorial_benchmark.cpp"
  "benchmark/fibonacci_benchmark.cpp"
  "benchmark/fibonacci_sequence_benchmark.cpp"
  "benchmark/first_missing_positive_benchmark.cpp"
  "benchmark/fizzbuzz_benchmark.cpp"
  "benchmark/gcd_benchmark.cpp"
  "benchmark/house_robber_benchmark.cpp"
  "benchmark/graph/balanced_binary_tree_benchmark.cpp"
  "benchmark/graph/breadth_first_search_benchmark.cpp"
  "benchmark/graph/depth_first_search_benchmark.cpp"
  "benchmark/graph/subsets_benchmark.cpp"
  "benchmark/last_stone_weight_benchmark.cpp"
  "benchmark/longest_consecutive_sequence_benchmark.cpp"
  "benchmark/lru_cache_benchmark.cpp"
  "benchmark/majority_element_benchmark.cpp"
  "benchmark/maximum_subarray_benchmark.cpp"
  "benchmark/meeting_rooms_benchmark.cpp"
  "benchmark/move_zeroes_benchmark.cpp"
  "benchmark/palindrome_benchmark.cpp"
  "benchmark/palindromic_number_benchmark.cpp"
  "benchmark/primality_benchmark.cpp"
  "benchmark/product_except_self_benchmark.cpp"
  "benchmark/project_euler/p0001_multiples_of_3_or_5_benchmark.cpp"
  "benchmark/search/binary_search_benchmark.cpp"
  "benchmark/set_matrix_zeroes_benchmark.cpp"
  "benchmark/sonar_benchmark.cpp"
  "benchmark/sorting/bubble_sort_benchmark.cpp"
  "benchmark/sorting/insertion_sort_benchmark.cpp"
  "benchmark/sorting/quicksort_benchmark.cpp"
  "benchmark/sub_array_sums_benchmark.cpp"
  "benchmark/top_k_frequent_elements_benchmark.cpp"
  "benchmark/tower_of_hanoi_benchmark.cpp"
  "benchmark/two_sum_benchmark.cpp"
  "benchmark/valid_anagram_benchmark.cpp"
  "benchmark/valid_parentheses_benchmark.cpp"
  "benchmark/valid_sudoku_benchmark.cpp"
)
get_target_property(forfun_benchmark benchmark_driver SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/benchmark/"
  PREFIX "Source files"
  FILES ${forfun_benchmark}
)
target_link_libraries(
  benchmark_driver
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  benchmark_driver
  PRIVATE forfun
  PRIVATE forfun_c
  PRIVATE forfun_common
  PRIVATE forfun_graph
  PRIVATE forfun_search
  PRIVATE forfun_sorting
)
forfun_common_target_compile_options(benchmark_driver)

add_executable(
  benchmark_driver_experimental
)
set_target_properties(benchmark_driver_experimental PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(benchmark_driver_experimental PROPERTIES CXX_STANDARD 23)
set_target_properties(benchmark_driver_experimental PROPERTIES CXX_STANDARD_REQUIRED ON)
target_sources(
  benchmark_driver_experimental
  PRIVATE
  "benchmark/benchmark.cpp"
  "benchmark/add_two_numbers_benchmark.cpp"
  "benchmark/container/forward_list_benchmark.cpp"
  "benchmark/container/list_benchmark.cpp"
)
get_target_property(
  forfun_experimental_benchmark
  benchmark_driver_experimental SOURCES
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/benchmark/"
  PREFIX "Source files"
  FILES ${forfun_experimental_benchmark}
)
target_link_libraries(
  benchmark_driver_experimental
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  benchmark_driver_experimental
  PRIVATE forfun
  PRIVATE forfun_experimental
  PRIVATE forfun_c_experimental
)
forfun_common_target_compile_options(benchmark_driver_experimental)

add_executable(
  static_test_driver
)
set_target_properties(static_test_driver PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(static_test_driver PROPERTIES CXX_STANDARD 23)
set_target_properties(static_test_driver PROPERTIES CXX_STANDARD_REQUIRED ON)
target_sources(
  static_test_driver
  PRIVATE
  "test/common/concepts_static_test.cpp"
  "test/contains_duplicate_static_test.cpp"
  "test/fibonacci_static_test.cpp"
  "test/graph/binary_tree_node_static_test.cpp"
  "test/majority_element_static_test.cpp"
  "test/maximum_subarray_static_test.cpp"
  "test/palindromic_number_static_test.cpp"
  "test/two_sum_static_test.cpp"
)
get_target_property(forfun_static_tests static_test_driver SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${forfun_static_tests}
)
target_link_libraries(
  static_test_driver
  PRIVATE Catch2::Catch2WithMain
)
target_link_libraries(
  static_test_driver
  PRIVATE forfun
  PRIVATE forfun_common
)
forfun_common_target_compile_options(static_test_driver)
