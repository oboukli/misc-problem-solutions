# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

add_executable(static_test_driver)
add_executable(test_driver)
add_executable(test_driver_experimental)
add_executable(test_driver_lock_free)

include(cmake/TargetHelpers.cmake)

find_package(Catch2 3 REQUIRED)
find_package(mimalloc CONFIG REQUIRED)

forfun_target_config(
  static_test_driver
  SOURCES_DIR "test"
  SOURCES
    "array_concatenation_statictest.cpp"
    "common/concepts_statictest.cpp"
    "common/limits_statictest.cpp"
    "common/type_traits_statictest.cpp"
    "concurrency/spsc_bound_queue_statictest.cpp"
    "container/forward_list_cycle_statictest.cpp"
    "container/forward_list_statictest.cpp"
    "container/internal/list_const_iterator_statictest.cpp"
    "container/internal/list_iterator_statictest.cpp"
    "container/list_statictest.cpp"
    "container/trie_statictest.cpp"
    "contains_duplicate_statictest.cpp"
    "daily_temperatures_statictest.cpp"
    "factorial_statictest.cpp"
    "fibonacci_statictest.cpp"
    "first_missing_positive_statictest.cpp"
    "graph/binary_tree_node_statictest.cpp"
    "hamming_weight_statictest.cpp"
    "majority_element_statictest.cpp"
    "math/math_statictest.cpp"
    "maximum_subarray_statictest.cpp"
    "missing_number_statictest.cpp"
    "palindromic_number_statictest.cpp"
    "permutation_in_string_statictest.cpp"
    "product_except_self_statictest.cpp"
    "project_euler/p0001_multiples_of_3_or_5_statictest.cpp"
    "search/binary_search_statictest.cpp"
    "search/koko_eating_bananas_statictest.cpp"
    "search/minimum_rotated_element_statictest.cpp"
    "sequence/longest_non_repeating_substring_statictest.cpp"
    "single_number_statictest.cpp"
    "sorting/quicksort_statictest.cpp"
    "sub_array_sums_statictest.cpp"
    "tower_of_hanoi_statictest.cpp"
    "trapping_rainwater_statictest.cpp"
    "two_sum_statictest.cpp"
)
target_link_libraries(
  static_test_driver
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  static_test_driver
  PRIVATE
    forfun_common
    forfun_core
    forfun_experimental
    forfun_graph
    forfun_lock_free
    forfun_math
    forfun_search
    forfun_sequence
    forfun_sorting
)

forfun_target_config(
  test_driver
  HEADERS_DIR "test"
  SOURCES_DIR "test"
  HEADERS
    "catch2_custom/matchers.hpp"
  SOURCES
    "add_two_numbers_test.cpp"
    "array_concatenation_test.cpp"
    "best_time_to_buy_and_sell_stock_test.cpp"
    "catch2_custom/matchers_test.cpp"
    "catch2_custom/matchers.cpp"
    "common/io_test.cpp"
    "container_with_most_water_test.cpp"
    "contains_duplicate_test.cpp"
    "daily_temperatures_test.cpp"
    "encode_and_decode_strings_test.cpp"
    "evaluate_reverse_polish_notation_test.cpp"
    "factorial_test.cpp"
    "fibonacci_sequence_test.cpp"
    "fibonacci_test.cpp"
    "first_missing_positive_test.cpp"
    "fizzbuzz_test.cpp"
    "gcd_test.cpp"
    "graph/balanced_binary_tree_test.cpp"
    "graph/binary_tree_diameter_test.cpp"
    "graph/binary_tree_node_test.cpp"
    "graph/breadth_first_search_test.cpp"
    "graph/depth_first_search_test.cpp"
    "graph/invert_binary_tree_test.cpp"
    "group_anagrams_test.cpp"
    "hamming_weight_test.cpp"
    "house_robber_test.cpp"
    "last_stone_weight_test.cpp"
    "longest_consecutive_sequence_test.cpp"
    "lru_cache_test.cpp"
    "majority_element_test.cpp"
    "math/math_test.cpp"
    "maximum_subarray_test.cpp"
    "meeting_rooms_test.cpp"
    "missing_number_test.cpp"
    "move_zeroes_test.cpp"
    "palindrome_test.cpp"
    "palindromic_number_test.cpp"
    "permutation_in_string_test.cpp"
    "primality_test.cpp"
    "product_except_self_test.cpp"
    "project_euler/p0001_multiples_of_3_or_5_test.cpp"
    "search/binary_search_test.cpp"
    "search/koko_eating_bananas_test.cpp"
    "search/minimum_rotated_element_test.cpp"
    "search/search_matrix_test.cpp"
    "sequence/longest_non_repeating_substring_test.cpp"
    "set_matrix_zeroes_test.cpp"
    "single_number_test.cpp"
    "sonar_test.cpp"
    "sorting/bubble_sort_test.cpp"
    "sorting/insertion_sort_test.cpp"
    "sorting/quicksort_test.cpp"
    "squares_sorted_array_test.cpp"
    "sub_array_sums_test.cpp"
    "subsets_test.cpp"
    "three_sum_test.cpp"
    "top_k_frequent_elements_test.cpp"
    "tower_of_hanoi_test.cpp"
    "trapping_rainwater_test.cpp"
    "two_sum_test.cpp"
    "valid_anagram_test.cpp"
    "valid_parentheses_test.cpp"
    "valid_sudoku_test.cpp"
)
target_link_libraries(
  test_driver
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  test_driver
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
  test_driver_experimental
  SOURCES_DIR "test"
  SOURCES
    "add_two_numbers_c_test.cpp"
    "catch2_custom/test_run_listener.cpp"
    "container/forward_list_cycle_test.cpp"
    "container/forward_list_test.cpp"
    "container/internal/list_const_iterator_test.cpp"
    "container/internal/list_iterator_test.cpp"
    "container/list_test.cpp"
    "container/min_stack_test.cpp"
    "container/trie_test.cpp"
    "mem/mem_test.cpp"
    "shim/allocator_test.cpp"
)
target_link_libraries(
  test_driver_experimental
  PRIVATE
    Catch2::Catch2WithMain
    mimalloc
)
target_link_libraries(
  test_driver_experimental
  PRIVATE
    forfun_experimental
    forfun_experimental_c
)

forfun_target_config(
  test_driver_lock_free
  SOURCES_DIR "test"
  SOURCES
    "concurrency/spsc_bound_queue_test.cpp"
)
target_link_libraries(
  test_driver_lock_free
  PRIVATE
    Catch2::Catch2WithMain
)
target_link_libraries(
  test_driver_lock_free
  PRIVATE
    forfun_lock_free
)

include(Catch)

catch_discover_tests(test_driver)
catch_discover_tests(test_driver_experimental)
catch_discover_tests(test_driver_lock_free)
