# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

add_executable(benchmark_driver)
add_executable(benchmark_driver_experimental)
add_executable(benchmark_driver_lock_free)

include(cmake/TargetHelpers.cmake)

find_package(Catch2 3 REQUIRED)
find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)

forfun_target_config(
  benchmark_driver
  SOURCES_DIR "benchmark"
  SOURCES
    "array_concatenation_benchmark.cpp"
    "benchmark.cpp"
    "best_time_to_buy_and_sell_stock_benchmark.cpp"
    "container_with_most_water_benchmark.cpp"
    "contains_duplicate_benchmark.cpp"
    "daily_temperatures_benchmark.cpp"
    "encode_and_decode_strings_benchmark.cpp"
    "evaluate_reverse_polish_notation_benchmark.cpp"
    "factorial_benchmark.cpp"
    "fibonacci_benchmark.cpp"
    "fibonacci_sequence_benchmark.cpp"
    "first_missing_positive_benchmark.cpp"
    "fizzbuzz_benchmark.cpp"
    "gcd_benchmark.cpp"
    "graph/balanced_binary_tree_benchmark.cpp"
    "graph/binary_tree_diameter_benchmark.cpp"
    "graph/breadth_first_search_benchmark.cpp"
    "graph/depth_first_search_benchmark.cpp"
    "graph/invert_binary_tree_benchmark.cpp"
    "group_anagrams_benchmark.cpp"
    "hamming_weight_benchmark.cpp"
    "house_robber_benchmark.cpp"
    "last_stone_weight_benchmark.cpp"
    "longest_consecutive_sequence_benchmark.cpp"
    "lru_cache_benchmark.cpp"
    "majority_element_benchmark.cpp"
    "math/math_benchmark.cpp"
    "maximum_subarray_benchmark.cpp"
    "meeting_rooms_benchmark.cpp"
    "missing_number_benchmark.cpp"
    "move_zeroes_benchmark.cpp"
    "palindrome_benchmark.cpp"
    "palindromic_number_benchmark.cpp"
    "permutation_in_string_benchmark.cpp"
    "primality_benchmark.cpp"
    "product_except_self_benchmark.cpp"
    "project_euler/p0001_multiples_of_3_or_5_benchmark.cpp"
    "search/binary_search_benchmark.cpp"
    "search/koko_eating_bananas_benchmark.cpp"
    "search/minimum_rotated_element_benchmark.cpp"
    "search/search_matrix_benchmark.cpp"
    "sequence/longest_non_repeating_substring_benchmark.cpp"
    "set_matrix_zeroes_benchmark.cpp"
    "single_number_benchmark.cpp"
    "sonar_benchmark.cpp"
    "sorting/bubble_sort_benchmark.cpp"
    "sorting/insertion_sort_benchmark.cpp"
    "sorting/quicksort_benchmark.cpp"
    "squares_sorted_array_benchmark.cpp"
    "sub_array_sums_benchmark.cpp"
    "subsets_benchmark.cpp"
    "three_sum_benchmark.cpp"
    "top_k_frequent_elements_benchmark.cpp"
    "tower_of_hanoi_benchmark.cpp"
    "trapping_rainwater_benchmark.cpp"
    "two_sum_benchmark.cpp"
    "valid_anagram_benchmark.cpp"
    "valid_parentheses_benchmark.cpp"
    "valid_sudoku_benchmark.cpp"
)
target_link_libraries(
  benchmark_driver
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  benchmark_driver
  PRIVATE
    forfun_common
    forfun_core
    forfun_core_c
    forfun_graph
    forfun_math
    forfun_search
    forfun_sequence
    forfun_sorting
)

forfun_target_config(
  benchmark_driver_experimental
  SOURCES_DIR "benchmark"
  SOURCES
    "add_two_numbers_benchmark.cpp"
    "benchmark.cpp"
    "container/forward_list_benchmark.cpp"
    "container/forward_list_cycle_benchmark.cpp"
    "container/list_benchmark.cpp"
    "container/min_stack_benchmark.cpp"
    "container/trie_benchmark.cpp"
)
target_link_libraries(
  benchmark_driver_experimental
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  benchmark_driver_experimental
  PRIVATE
    forfun_core
    forfun_experimental
    forfun_experimental_c
)

forfun_target_config(
  benchmark_driver_lock_free
  SOURCES_DIR "benchmark"
  SOURCES
    "benchmark.cpp"
    "concurrency/spsc_bound_queue_benchmark.cpp"
)
target_link_libraries(
  benchmark_driver_lock_free
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  benchmark_driver_lock_free
  PRIVATE
    forfun_lock_free
)
