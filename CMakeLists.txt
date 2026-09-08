# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31)

include(cmake/Features.cmake)

project(
  ForFunDsa
  VERSION 0.1.0
  LANGUAGES
    C
    CXX
)

add_library(forfun_common)
add_library(forfun_core)
add_library(forfun_experimental)
add_library(forfun_graph)
add_library(forfun_lock_free)
add_library(forfun_math)
add_library(forfun_search)
add_library(forfun_sequence)
add_library(forfun_sorting)

# C library
add_library(forfun_core_c)

# Thread-unsafe C library
add_library(forfun_experimental_c STATIC)

include(cmake/TargetHelpers.cmake)

find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(mimalloc CONFIG REQUIRED)

forfun_target_config(
  forfun_common
  HEADERS
    "forfun/common/concepts.hpp"
    "forfun/common/io.hpp"
    "forfun/common/limits.hpp"
    "forfun/common/type_traits.hpp"
  SOURCES
    "forfun/common/concepts.cpp"
    "forfun/common/io.cpp"
    "forfun/common/limits.cpp"
    "forfun/common/type_traits.cpp"
)

forfun_target_config(
  forfun_core
  HEADERS
    "forfun/add_two_numbers.hpp"
    "forfun/array_concatenation.hpp"
    "forfun/best_time_to_buy_and_sell_stock.hpp"
    "forfun/container_with_most_water.hpp"
    "forfun/contains_duplicate.hpp"
    "forfun/daily_temperatures.hpp"
    "forfun/encode_and_decode_strings.hpp"
    "forfun/evaluate_reverse_polish_notation.hpp"
    "forfun/factorial.hpp"
    "forfun/fibonacci_sequence.hpp"
    "forfun/fibonacci.hpp"
    "forfun/first_missing_positive.hpp"
    "forfun/fizzbuzz.hpp"
    "forfun/gcd.hpp"
    "forfun/group_anagrams.hpp"
    "forfun/hamming_weight.hpp"
    "forfun/house_robber.hpp"
    "forfun/last_stone_weight.hpp"
    "forfun/longest_consecutive_sequence.hpp"
    "forfun/lru_cache.hpp"
    "forfun/majority_element.hpp"
    "forfun/maximum_subarray.hpp"
    "forfun/meeting_rooms.hpp"
    "forfun/missing_number.hpp"
    "forfun/move_zeroes.hpp"
    "forfun/palindrome.hpp"
    "forfun/palindromic_number.hpp"
    "forfun/permutation_in_string.hpp"
    "forfun/primality.hpp"
    "forfun/product_except_self.hpp"
    "forfun/project_euler/p0001_multiples_of_3_or_5.hpp"
    "forfun/set_matrix_zeroes.hpp"
    "forfun/single_number.hpp"
    "forfun/sonar.hpp"
    "forfun/squares_sorted_array.hpp"
    "forfun/sub_array_sums.hpp"
    "forfun/subsets.hpp"
    "forfun/three_sum.hpp"
    "forfun/top_k_frequent_elements.hpp"
    "forfun/tower_of_hanoi.hpp"
    "forfun/trapping_rainwater.hpp"
    "forfun/two_sum.hpp"
    "forfun/valid_anagram.hpp"
    "forfun/valid_parentheses.hpp"
    "forfun/valid_sudoku.hpp"
  SOURCES
    "forfun/add_two_numbers.cpp"
    "forfun/array_concatenation.cpp"
    "forfun/best_time_to_buy_and_sell_stock.cpp"
    "forfun/container_with_most_water.cpp"
    "forfun/contains_duplicate.cpp"
    "forfun/daily_temperatures.cpp"
    "forfun/encode_and_decode_strings.cpp"
    "forfun/evaluate_reverse_polish_notation.cpp"
    "forfun/factorial.cpp"
    "forfun/fibonacci_sequence.cpp"
    "forfun/fibonacci.cpp"
    "forfun/first_missing_positive.cpp"
    "forfun/fizzbuzz.cpp"
    "forfun/gcd.cpp"
    "forfun/group_anagrams.cpp"
    "forfun/hamming_weight.cpp"
    "forfun/house_robber.cpp"
    "forfun/last_stone_weight.cpp"
    "forfun/longest_consecutive_sequence.cpp"
    "forfun/lru_cache.cpp"
    "forfun/majority_element.cpp"
    "forfun/maximum_subarray.cpp"
    "forfun/meeting_rooms.cpp"
    "forfun/missing_number.cpp"
    "forfun/move_zeroes.cpp"
    "forfun/palindrome.cpp"
    "forfun/palindromic_number.cpp"
    "forfun/permutation_in_string.cpp"
    "forfun/primality.cpp"
    "forfun/product_except_self.cpp"
    "forfun/project_euler/p0001_multiples_of_3_or_5.cpp"
    "forfun/set_matrix_zeroes.cpp"
    "forfun/single_number.cpp"
    "forfun/sonar.cpp"
    "forfun/squares_sorted_array.cpp"
    "forfun/sub_array_sums.cpp"
    "forfun/subsets.cpp"
    "forfun/three_sum.cpp"
    "forfun/top_k_frequent_elements.cpp"
    "forfun/tower_of_hanoi.cpp"
    "forfun/trapping_rainwater.cpp"
    "forfun/two_sum.cpp"
    "forfun/valid_anagram.cpp"
    "forfun/valid_parentheses.cpp"
    "forfun/valid_sudoku.cpp"
)

forfun_target_config(
  forfun_experimental
  HEADERS
    "forfun/container/forward_list_cycle.hpp"
    "forfun/container/forward_list_node.hpp"
    "forfun/container/forward_list.hpp"
    "forfun/container/internal/list_bidirectional_iterator_helper.hpp"
    "forfun/container/internal/list_const_iterator.hpp"
    "forfun/container/internal/list_iterator.hpp"
    "forfun/container/internal/list_node.hpp"
    "forfun/container/list.hpp"
    "forfun/container/min_stack.hpp"
    "forfun/container/trie.hpp"
  SOURCES
    "forfun/container/forward_list_cycle.cpp"
    "forfun/container/forward_list_node.cpp"
    "forfun/container/forward_list.cpp"
    "forfun/container/internal/list_bidirectional_iterator_helper.cpp"
    "forfun/container/internal/list_const_iterator.cpp"
    "forfun/container/internal/list_iterator.cpp"
    "forfun/container/internal/list_node.cpp"
    "forfun/container/list.cpp"
    "forfun/container/min_stack.cpp"
    "forfun/container/trie.cpp"
)
target_link_libraries(
  forfun_experimental
  PRIVATE
    Microsoft.GSL::GSL
)

forfun_target_config(
  forfun_graph
  HEADERS
    "forfun/graph/balanced_binary_tree.hpp"
    "forfun/graph/binary_tree_diameter.hpp"
    "forfun/graph/binary_tree_node.hpp"
    "forfun/graph/breadth_first_search.hpp"
    "forfun/graph/depth_first_search.hpp"
    "forfun/graph/invert_binary_tree.hpp"
    "forfun/graph/vertex.hpp"
  SOURCES
    "forfun/graph/balanced_binary_tree.cpp"
    "forfun/graph/binary_tree_diameter.cpp"
    "forfun/graph/binary_tree_node.cpp"
    "forfun/graph/breadth_first_search.cpp"
    "forfun/graph/depth_first_search.cpp"
    "forfun/graph/invert_binary_tree.cpp"
    "forfun/graph/vertex.cpp"
)

forfun_target_config(
  forfun_lock_free
  HEADERS
    "forfun/concurrency/spsc_bound_queue.hpp"
  SOURCES
    "forfun/concurrency/spsc_bound_queue.cpp"
)

forfun_target_config(
  forfun_math
  HEADERS
    "forfun/math/math.hpp"
  SOURCES
    "forfun/math/math.cpp"
)

forfun_target_config(
  forfun_search
  HEADERS
    "forfun/search/binary_search.hpp"
    "forfun/search/koko_eating_bananas.hpp"
    "forfun/search/minimum_rotated_element.hpp"
    "forfun/search/search_matrix.hpp"
  SOURCES
    "forfun/search/binary_search.cpp"
    "forfun/search/koko_eating_bananas.cpp"
    "forfun/search/minimum_rotated_element.cpp"
    "forfun/search/search_matrix.cpp"
)
target_link_libraries(
  forfun_search
  PRIVATE
    forfun_math
)

forfun_target_config(
  forfun_sequence
  HEADERS
    "forfun/sequence/longest_non_repeating_substring.hpp"
  SOURCES
    "forfun/sequence/longest_non_repeating_substring.cpp"
)

forfun_target_config(
  forfun_sorting
  HEADERS
    "forfun/sorting/bubble_sort.hpp"
    "forfun/sorting/insertion_sort.hpp"
    "forfun/sorting/quicksort.hpp"
  SOURCES
    "forfun/sorting/bubble_sort.cpp"
    "forfun/sorting/insertion_sort.cpp"
    "forfun/sorting/quicksort.cpp"
)

forfun_target_config(
  forfun_core_c
  HEADERS
    "forfun_c/palindrome.h"
    "forfun_c/single_number.h"
  SOURCES
    "forfun_c/palindrome.c"
    "forfun_c/single_number.c"
)

forfun_target_config(
  forfun_experimental_c
  HEADERS
    "forfun_c/add_two_numbers.h"
    "forfun_c/common.h"
    "forfun_c/container/forward_list.h"
    "forfun_c/mem/mem.h"
    "forfun_c/shim/allocator.h"
  SOURCES
    "forfun_c/add_two_numbers.c"
    "forfun_c/common.c"
    "forfun_c/container/forward_list.c"
    "forfun_c/mem/mem.c"
    "forfun_c/shim/allocator.c"
)
target_link_libraries(
  forfun_experimental_c
  PRIVATE
    mimalloc
)
# C99 is required only for including mimalloc headers.
set_target_properties(
  forfun_experimental_c
  PROPERTIES
    C_STANDARD 99
)

if(FORFUN_BUILD_BENCHMARK_TARGETS)
  include(cmake/BenchmarkTargets.cmake)
endif()

if(FORFUN_BUILD_CUSTOM_TARGETS)
  include(cmake/CodeFormat.cmake)
endif()

if(FORFUN_BUILD_FUZZ_TARGETS)
  include(cmake/FuzzTargets.cmake)
endif()

if(FORFUN_BUILD_TEST_TARGETS)
  include(cmake/TestTargets.cmake)
endif()

if(FORFUN_CONFIGURE_INSTALLATION)
  include(cmake/Install.cmake)
endif()
