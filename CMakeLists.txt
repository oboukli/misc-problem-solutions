# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)

project(
  ForFun
)

add_library(forfun)
add_library(forfun_common)
add_library(forfun_experimental)
add_library(forfun_graph)
add_library(forfun_search)
add_library(forfun_sorting)

add_library(forfun_c)

# Defines and exports global thread-unsafe state.
add_library(forfun_c_experimental STATIC)

add_executable(test_driver)
add_executable(test_driver_experimental)
add_executable(static_test_driver)

add_executable(benchmark_driver)
add_executable(benchmark_driver_experimental)

include(cmake/CompileOptions.cmake)

target_include_directories(
  forfun
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/add_two_numbers.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/array_concatenation.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/best_time_to_buy_and_sell_stock.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container_with_most_water.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/contains_duplicate.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/encode_and_decode_strings.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/evaluate_reverse_polish_notation.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/factorial.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/fibonacci_sequence.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/fibonacci.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/first_missing_positive.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/fizzbuzz.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/gcd.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/group_anagrams.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/house_robber.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/last_stone_weight.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/longest_consecutive_sequence.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/lru_cache.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/majority_element.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/maximum_subarray.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/meeting_rooms.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/move_zeroes.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/palindrome.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/palindromic_number.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/primality.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/product_except_self.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/set_matrix_zeroes.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sonar.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/squares_sorted_array.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sub_array_sums.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/top_k_frequent_elements.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/tower_of_hanoi.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/trie.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/two_sum.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/valid_anagram.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/valid_parentheses.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/valid_sudoku.hpp"
)
target_sources(
  forfun
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/add_two_numbers.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/array_concatenation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/best_time_to_buy_and_sell_stock.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container_with_most_water.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/contains_duplicate.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/encode_and_decode_strings.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/evaluate_reverse_polish_notation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/factorial.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/fibonacci_sequence.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/fibonacci.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/first_missing_positive.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/fizzbuzz.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/gcd.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/group_anagrams.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/house_robber.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/last_stone_weight.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/longest_consecutive_sequence.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/lru_cache.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/majority_element.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/maximum_subarray.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/meeting_rooms.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/move_zeroes.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/palindrome.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/palindromic_number.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/primality.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/product_except_self.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/project_euler/p0001_multiples_of_3_or_5.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/set_matrix_zeroes.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sonar.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/squares_sorted_array.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sub_array_sums.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/top_k_frequent_elements.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/tower_of_hanoi.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/trie.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/two_sum.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/valid_anagram.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/valid_parentheses.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/valid_sudoku.cpp"
)
get_target_property(forfun_headers forfun HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/"
  PREFIX "Header files"
  FILES ${forfun_headers}
)
get_target_property(forfun_sources forfun SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/"
  PREFIX "Source files"
  FILES ${forfun_sources}
)
forfun_common_target_compile_options(forfun)

target_include_directories(
  forfun_common
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_common
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/common/concepts.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/common/io.hpp"
)
target_sources(
  forfun_common
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/common/concepts.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/common/io.cpp"
)
get_target_property(forfun_common_headers forfun_common HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/common/"
  PREFIX "Header files"
  FILES ${forfun_common_headers}
)
get_target_property(forfun_common_sources forfun_common SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/common/"
  PREFIX "Source files"
  FILES ${forfun_common_sources}
)
forfun_common_target_compile_options(forfun_common)

target_include_directories(
  forfun_graph
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_graph
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/balanced_binary_tree.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/binary_tree_node.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/breadth_first_search.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/depth_first_search.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/subsets.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/vertex.hpp"
)
target_sources(
  forfun_graph
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/balanced_binary_tree.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/binary_tree_node.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/breadth_first_search.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/depth_first_search.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/subsets.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/vertex.cpp"
)
get_target_property(forfun_graph_headers forfun_graph HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/graph/"
  PREFIX "Header files"
  FILES ${forfun_graph_headers}
)
get_target_property(forfun_graph_sources forfun_graph SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/graph/"
  PREFIX "Source files"
  FILES ${forfun_graph_sources}
)
forfun_common_target_compile_options(forfun_graph)

target_include_directories(
  forfun_search
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_search
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/search/binary_search.hpp"
)
target_sources(
  forfun_search
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/search/binary_search.cpp"
)
get_target_property(forfun_search_headers forfun_search HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/search/"
  PREFIX "Header files"
  FILES ${forfun_search_headers}
)
get_target_property(forfun_search_sources forfun_search SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/search/"
  PREFIX "Source files"
  FILES ${forfun_search_sources}
)
forfun_common_target_compile_options(forfun_search)

target_include_directories(
  forfun_sorting
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_sorting
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sorting/bubble_sort.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sorting/insertion_sort.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sorting/quicksort.hpp"
)
target_sources(
  forfun_sorting
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sorting/bubble_sort.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sorting/insertion_sort.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sorting/quicksort.cpp"
)
get_target_property(forfun_sorting_headers forfun_sorting HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/sorting/"
  PREFIX "Header files"
  FILES ${forfun_sorting_headers}
)
get_target_property(forfun_sorting_sources forfun_sorting SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/sorting/"
  PREFIX "Source files"
  FILES ${forfun_sorting_sources}
)
forfun_common_target_compile_options(forfun_sorting)

target_include_directories(
  forfun_c
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_c
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/palindrome.h"
)
target_sources(
  forfun_c
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/palindrome.c"
)
get_target_property(forfun_c_headers forfun_c HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/"
  PREFIX "Header files"
  FILES ${forfun_c_headers}
)
get_target_property(forfun_c_sources forfun_c SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/"
  PREFIX "Source files"
  FILES ${forfun_c_sources}
)
forfun_common_target_compile_options(forfun_c)

find_package(mimalloc CONFIG REQUIRED)

target_include_directories(
  forfun_c_experimental
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_c_experimental
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/add_two_numbers.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/container/forward_list.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/mem/mem.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/shim/allocator.h"
)
target_sources(
  forfun_c_experimental
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/add_two_numbers.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/container/forward_list.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/mem/mem.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/shim/allocator.c"
)
get_target_property(
  forfun_c_experimental_headers
  forfun_c_experimental
  HEADER_SET
)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun_c/"
  PREFIX "Header files"
  FILES ${forfun_c_experimental_headers}
)
get_target_property(forfun_c_experimental_sources forfun_c_experimental SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun_c/"
  PREFIX "Source files"
  FILES ${forfun_c_experimental_sources}
)
target_link_libraries(
  forfun_c_experimental
  PRIVATE mimalloc
)
forfun_common_target_compile_options(forfun_c_experimental)

find_package(Microsoft.GSL CONFIG REQUIRED)

target_include_directories(
  forfun_experimental
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_sources(
  forfun_experimental
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/forward_list.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/internal/forward_list_node.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/internal/list_const_iterator.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/internal/list_iterator_helper.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/internal/list_iterator.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/internal/list_node.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/container/list.hpp"
)
target_sources(
  forfun_experimental
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/forward_list.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/internal/forward_list_node.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/internal/list_const_iterator.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/internal/list_iterator_helper.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/internal/list_iterator.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/internal/list_node.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/container/list.cpp"
)
get_target_property(forfun_experimental_headers forfun_experimental HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/forfun/"
  PREFIX "Header files"
  FILES ${forfun_experimental_headers}
)
get_target_property(forfun_experimental_sources forfun_experimental SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src/forfun/"
  PREFIX "Source files"
  FILES ${forfun_experimental_sources}
)
target_link_libraries(
  forfun_experimental
  PRIVATE Microsoft.GSL::GSL
)
forfun_common_target_compile_options(forfun_experimental)

find_package(Catch2 3 REQUIRED)

target_sources(
  test_driver
  PRIVATE
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/test"
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/test/catch2_custom/matchers.hpp"
)
target_sources(
  test_driver
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/test/add_two_numbers_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/array_concatenation_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/best_time_to_buy_and_sell_stock_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/common/io_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container_with_most_water_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/contains_duplicate_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/encode_and_decode_strings_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/evaluate_reverse_polish_notation_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/factorial_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/fibonacci_sequence_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/fibonacci_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/first_missing_positive_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/fizzbuzz_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/gcd_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/balanced_binary_tree_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/binary_tree_node_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/breadth_first_search_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/depth_first_search_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/subsets_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/vertex_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/group_anagrams_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/house_robber_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/last_stone_weight_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/longest_consecutive_sequence_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/lru_cache_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/majority_element_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/maximum_subarray_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/meeting_rooms_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/move_zeroes_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/palindrome_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/palindromic_number_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/primality_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/product_except_self_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/project_euler/p0001_multiples_of_3_or_5_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/search/binary_search_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/set_matrix_zeroes_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sonar_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sorting/bubble_sort_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sorting/insertion_sort_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sorting/quicksort_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/squares_sorted_array_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sub_array_sums_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/top_k_frequent_elements_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/tower_of_hanoi_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/trie_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/two_sum_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/valid_anagram_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/valid_parentheses_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/valid_sudoku_test.cpp"
)
get_target_property(test_driver_headers test_driver HEADER_SET)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/"
  PREFIX "Header files"
  FILES ${test_driver_headers}
)
get_target_property(test_driver_sources test_driver SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${test_driver_sources}
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

target_sources(
  test_driver_experimental
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/test/add_two_numbers_c_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/catch2_custom/test_run_listener.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/forward_list_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/internal/list_const_iterator_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/internal/list_iterator_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/list_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/mem/mem_test.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/shim/allocator_test.cpp"
)
get_target_property(
  test_driver_experimental_sources
  test_driver_experimental
  SOURCES
)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${test_driver_experimental_sources}
)
target_link_libraries(
  test_driver_experimental
  PRIVATE Catch2::Catch2WithMain
  PRIVATE mimalloc
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

target_sources(
  benchmark_driver
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/array_concatenation_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/best_time_to_buy_and_sell_stock_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/container_with_most_water_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/contains_duplicate_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/encode_and_decode_strings_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/evaluate_reverse_polish_notation_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/factorial_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fibonacci_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fibonacci_sequence_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/first_missing_positive_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fizzbuzz_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/gcd_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/graph/balanced_binary_tree_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/graph/breadth_first_search_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/graph/depth_first_search_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/graph/subsets_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/group_anagrams_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/house_robber_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/last_stone_weight_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/longest_consecutive_sequence_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/lru_cache_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/majority_element_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/maximum_subarray_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/meeting_rooms_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/move_zeroes_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/palindrome_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/palindromic_number_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/primality_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/product_except_self_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/project_euler/p0001_multiples_of_3_or_5_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/search/binary_search_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/set_matrix_zeroes_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/sonar_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/sorting/bubble_sort_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/sorting/insertion_sort_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/sorting/quicksort_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/squares_sorted_array_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/sub_array_sums_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/top_k_frequent_elements_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/tower_of_hanoi_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/two_sum_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/valid_anagram_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/valid_parentheses_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/valid_sudoku_benchmark.cpp"
)
get_target_property(benchmark_driver_sources benchmark_driver SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/"
  PREFIX "Source files"
  FILES ${benchmark_driver_sources}
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

target_sources(
  benchmark_driver_experimental
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/add_two_numbers_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/container/forward_list_benchmark.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/container/list_benchmark.cpp"
)
get_target_property(
  benchmark_driver_experimental_sources
  benchmark_driver_experimental
  SOURCES
)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/"
  PREFIX "Source files"
  FILES ${benchmark_driver_experimental_sources}
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

target_sources(
  static_test_driver
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/test/common/concepts_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/internal/list_const_iterator_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/internal/list_iterator_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/container/list_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/contains_duplicate_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/fibonacci_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/graph/binary_tree_node_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/majority_element_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/maximum_subarray_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/palindromic_number_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/sorting/insertion_sort_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/squares_sorted_array_statictest.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/two_sum_statictest.cpp"
)
get_target_property(static_test_driver_sources static_test_driver SOURCES)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/"
  PREFIX "Source files"
  FILES ${static_test_driver_sources}
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

if(FORFUN_BUILD_FUZZING_DRIVER)
  enable_testing()

  include(GoogleTest)

  add_subdirectory(fuzztest)

  fuzztest_setup_fuzzing_flags()

  add_executable(
    fuzzing_driver
  )
  set_target_properties(
    fuzzing_driver
    PROPERTIES
      CXX_EXTENSIONS OFF
      CXX_STANDARD 23
      CXX_STANDARD_REQUIRED ON
      LANGUAGE CXX
  )
  target_sources(
    fuzzing_driver
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/encode_and_decode_strings_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/evaluate_reverse_polish_notation_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/search/binary_search_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/sorting/bubble_sort_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/sorting/insertion_sort_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/sorting/quicksort_fuzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/squares_sorted_array_fuzz.cpp"
  )
  get_target_property(fuzzing_driver_sources fuzzing_driver SOURCES)
  source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/fuzz/"
    PREFIX "Source files"
    FILES ${fuzzing_driver_sources}
  )
  target_link_libraries(
    fuzzing_driver
    PRIVATE forfun
  )
  target_link_libraries(
    fuzzing_driver
    PRIVATE GTest::gmock
    PRIVATE GTest::gtest
  )
  link_fuzztest(fuzzing_driver)
  gtest_discover_tests(fuzzing_driver)
endif()

set_target_properties(
  forfun
  forfun_common
  forfun_experimental
  forfun_graph
  forfun_search
  forfun_sorting
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    LANGUAGE CXX
)

set_target_properties(
  benchmark_driver
  benchmark_driver_experimental
  static_test_driver
  test_driver
  test_driver_experimental
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    LANGUAGE CXX
)

set_target_properties(
  forfun_c
  forfun_c_experimental
  PROPERTIES
    C_EXTENSIONS OFF
    C_STANDARD 90
    C_STANDARD_REQUIRED ON
    LANGUAGE C
)
