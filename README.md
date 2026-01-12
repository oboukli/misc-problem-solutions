# Solutions in C and C++ to Miscellaneous Programming Problems

This is a repository of modern coding showcases and solutions to various popular
programming problems, written in C90, C++17, C++20, and C++23.

For some of the said problems, multiple solutions of varying efficiencies and
trade-offs are provided, along with benchmarks, and full test coverage.

All solutions are driven by extensive automated testing, in addition to being
statically and dynamically analyzed, and compiled under strict rules with the
latest Clang, GCC, and MSVC compilers.

This work may include code that experiment with non-production-grade techniques
and/or patterns, e.g. recursion.

See the [developer notes](docs/developer_notes.md) for more information.

## Technical showcases

The following is a partial list of standards, practices, paradigms, and tools
leveraged by this project:

- C (standard C90) and C++ (standard C++17, C++20, and C++23)
- The C and C++ standard libraries
- Strongly-typed approach, leveraging C++ templates and C++20 concepts
- Exception safety-aware design
- Const correctness is applied where applicable, except for fields
- Functional programming
- Generic programming
- Strict standard conformance and strict compilation rules
- Static analysis with Clang Tidy and Microsoft C++ Code Analysis
- Dynamic analysis
- LLVM-based sanitizer tools
- Target property-based CMake configuration
- Clean Git history and configuration
- Extensive testing using Catch2, FuzzTest, GTest, and CTest
- Development dependency management using vcpkg
- Own opinionated Clang Format configuration
- Conventional Commits
- GitHub Actions CI
- Benchmarking using nanobench
- Microsoft DevSkim
- EditorConfig
- Markdown
- Diagramming with Mermaid

## Index

| Problem                                                            | Source                                                                                                                                         |
| ---                                                                | ---                                                                                                                                            |
| Add Two Numbers                                                    | [`src/forfun/add_two_numbers.cpp`](src/forfun/add_two_numbers.cpp)                                                                             |
| Add Two Numbers (in C)                                             | [`src/forfun_c/add_two_numbers.c`](src/forfun_c/add_two_numbers.c)                                                                             |
| Balanced Binary Tree                                               | [`src/forfun/graph/balanced_binary_tree.cpp`](src/forfun/graph/balanced_binary_tree.cpp)                                                       |
| Best Time to Buy And Sell Stock                                    | [`include/forfun/best_time_to_buy_and_sell_stock.hpp`](include/forfun/best_time_to_buy_and_sell_stock.hpp)                                     |
| Binary Search                                                      | [`include/forfun/search/binary_search.hpp`](include/forfun/search/binary_search.hpp)                                                           |
| Breadth-First Search                                               | [`include/forfun/graph/breadth_first_search.hpp`](include/forfun/graph/breadth_first_search.hpp)                                               |
| Bubble Sort                                                        | [`include/forfun/sorting/bubble_sort.hpp`](include/forfun/sorting/bubble_sort.hpp)                                                             |
| Concatenation of Array                                             | [`include/forfun/array_concatenation.hpp`](include/forfun/array_concatenation.hpp)                                                             |
| Container with Most Water                                          | [`include/forfun/container_with_most_water.hpp`](include/forfun/container_with_most_water.hpp)                                                 |
| Contains Duplicate                                                 | [`include/forfun/contains_duplicate.hpp`](include/forfun/contains_duplicate.hpp)                                                               |
| Depth-First Search                                                 | [`include/forfun/graph/depth_first_search.hpp`](include/forfun/graph/depth_first_search.hpp)                                                   |
| Encode and Decode Strings                                          | [`include/forfun/encode_and_decode_strings.hpp`](include/forfun/encode_and_decode_strings.hpp)                                                 |
| Evaluate Reverse Polish Notation                                   | [`include/forfun/evaluate_reverse_polish_notation.hpp`](include/forfun/evaluate_reverse_polish_notation.hpp)                                   |
| Factorial                                                          | [`include/forfun/factorial.hpp`](include/forfun/factorial.hpp)                                                                                 |
| Fibonacci Sequence                                                 | [`include/forfun/fibonacci_sequence.hpp`](include/forfun/fibonacci_sequence.hpp)                                                               |
| First Missing Positive                                             | [`include/forfun/first_missing_positive.hpp`](include/forfun/first_missing_positive.hpp)                                                       |
| Fizz Buzz                                                          | [`include/forfun/fizzbuzz.hpp`](include/forfun/fizzbuzz.hpp)                                                                                   |
| Forward List                                                       | [`include/forfun/container/forward_list.hpp`](include/forfun/container/forward_list.hpp)                                                       |
| Forward List Cycle                                                 | [`include/forfun/container/forward_list_cycle.hpp`](include/forfun/container/forward_list_cycle.hpp)                                           |
| Greatest Common Divisor                                            | [`include/forfun/gcd.hpp`](include/forfun/gcd.hpp)                                                                                             |
| Group Anagrams                                                     | [`include/forfun/group_anagrams.hpp`](include/forfun/group_anagrams.hpp)                                                                       |
| Hamming Weight                                                     | [`include/forfun/hamming_weight.hpp`](include/forfun/hamming_weight.hpp)                                                                       |
| House Robber                                                       | [`include/forfun/house_robber.hpp`](include/forfun/house_robber.hpp)                                                                           |
| Insertion Sort                                                     | [`include/forfun/sorting/insertion_sort.hpp`](include/forfun/sorting/insertion_sort.hpp)                                                       |
| Integer division ceiling                                           | [`include/forfun/common/math.hpp`](include/forfun/common/math.hpp)                                                                             |
| Invert Binary Tree                                                 | [`src/forfun/graph/invert_binary_tree.cpp`](src/forfun/graph/invert_binary_tree.cpp)                                                           |
| Last Stone Weight                                                  | [`include/forfun/last_stone_weight.hpp`](include/forfun/last_stone_weight.hpp)                                                                 |
| Least Recently Used (LRU) Cache                                    | [`src/forfun/lru_cache.cpp`](src/forfun/lru_cache.cpp)                                                                                         |
| Linked List                                                        | [`include/forfun/container/list.hpp`](include/forfun/container/list.hpp)                                                                       |
| List Bidirectional Iterator                                        | [`include/forfun/container/internal/list_iterator.hpp`](include/forfun/container/internal/list_iterator.hpp)                                   |
| Longest Consecutive Sequence                                       | [`include/forfun/longest_consecutive_sequence.hpp`](include/forfun/longest_consecutive_sequence.hpp)                                           |
| Maximum Subarray                                                   | [`include/forfun/maximum_subarray.hpp`](include/forfun/maximum_subarray.hpp)                                                                   |
| Meeting Rooms (I, II)                                              | [`include/forfun/meeting_rooms.hpp`](include/forfun/meeting_rooms.hpp)                                                                         |
| Missing Number                                                     | [`include/forfun/missing_number.hpp`](include/forfun/missing_number.hpp)                                                                       |
| Move Zeroes                                                        | [`include/forfun/move_zeroes.hpp`](include/forfun/move_zeroes.hpp)                                                                             |
| Multiples of Three or Five                                         | [`include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp`](include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp)                     |
| Nth Fibonacci Number                                               | [`include/forfun/fibonacci.hpp`](include/forfun/fibonacci.hpp)                                                                                 |
| Number of Ships in a Rectangle                                     | [`src/forfun/sonar.cpp`](src/forfun/sonar.cpp)                                                                                                 |
| Palindrome                                                         | [`include/forfun/palindrome.hpp`](include/forfun/palindrome.hpp)                                                                               |
| Palindrome (in C)                                                  | [`src/forfun_c/palindrome.c`](src/forfun_c/palindrome.c)                                                                                       |
| Palindromic Number                                                 | [`src/forfun/palindromic_number.cpp`](src/forfun/palindromic_number.cpp)                                                                       |
| Primality Test                                                     | [`include/forfun/primality.hpp`](include/forfun/primality.hpp)                                                                                 |
| Product of Array Except Self                                       | [`include/forfun/product_except_self.hpp`](include/forfun/product_except_self.hpp)                                                             |
| Quicksort                                                          | [`include/forfun/sorting/quicksort.hpp`](include/forfun/sorting/quicksort.hpp)                                                                 |
| Reverse Forward List                                               | [`include/forfun/container/forward_list.hpp`](include/forfun/container/forward_list.hpp)                                                       |
| Search matrix                                                      | [`include/forfun/search_matrix.hpp`](include/forfun/search_matrix.hpp)                                                                         |
| Set Matrix Zeroes                                                  | [`src/forfun/set_matrix_zeroes.cpp`](src/forfun/set_matrix_zeroes.cpp)                                                                         |
| Single Number                                                      | [`include/forfun/single_number.hpp`](include/forfun/single_number.hpp)                                                                         |
| Squares of a Sorted Array                                          | [`include/forfun/squares_sorted_array.hpp`](include/forfun/squares_sorted_array.hpp)                                                           |
| Subsets                                                            | [`include/forfun/subsets.hpp`](include/forfun/subsets.hpp)                                                                                     |
| Sums of Subarrays of Length K                                      | [`include/forfun/sub_array_sums.hpp`](include/forfun/sub_array_sums.hpp)                                                                       |
| Three Sum (3SUM)                                                   | [`include/forfun/three_sum.hpp`](include/forfun/three_sum.hpp)                                                                                 |
| Top K Frequent Elements                                            | [`include/forfun/top_k_frequent_elements.hpp`](include/forfun/top_k_frequent_elements.hpp)                                                     |
| Tower of Hanoi                                                     | [`include/forfun/tower_of_hanoi.hpp`](include/forfun/tower_of_hanoi.hpp)                                                                       |
| Trapping Rainwater                                                 | [`include/forfun/trapping_rainwater.hpp`](include/forfun/trapping_rainwater.hpp)                                                               |
| Trie                                                               | [`include/forfun/trie.hpp`](include/forfun/trie.hpp)                                                                                           |
| Two Sum (I, II)                                                    | [`include/forfun/two_sum.hpp`](include/forfun/two_sum.hpp)                                                                                     |
| Two-pass Boyer-Moore Majority                                      | [`include/forfun/majority_element.hpp`](include/forfun/majority_element.hpp)                                                                   |
| Valid Anagram                                                      | [`include/forfun/valid_anagram.hpp`](include/forfun/valid_anagram.hpp)                                                                         |
| Valid Parentheses                                                  | [`src/forfun/valid_parentheses.cpp`](src/forfun/valid_parentheses.cpp)                                                                         |
| Valid Sudoku                                                       | [`include/forfun/valid_sudoku.hpp`](include/forfun/valid_sudoku.hpp)                                                                           |

## Disclaimer

The provided attempted solutions are not guaranteed to be correct, safe,
secure, optimal, or suitable for use in production. The code and coding style
may, or may not, follow best practice guidelines.

## License

### Problem licenses

Problem copyrights are reserved to their respective owners.

### Solution licenses

Solution code is released under an [MIT-style license](LICENSE).
Copyright © Omar Boukli-Hacene. All rights reserved.

SPDX license identifier: MIT.

---

Written for the joy of it 🪐
