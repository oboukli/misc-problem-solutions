# Solutions in C and C++ to Miscellaneous Programming Problems

This is a repository of modern coding showcases and solutions to various popular
programming problems, written in C90, C++17, C++20, and C++23.

For some of the said problems, multiple solutions of varying efficiencies and
trade-offs are provided, along with benchmarks.

All solutions are driven by extensive automated testing, in addition to being
statically and dynamically analyzed, and compiled under strict rules with the
latest Clang, GCC, and MSVC compilers.

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

| Problem                          | Standard | Source                                                                                                                     |
| ---                              | ---      | ---                                                                                                                        |
| Add Two Numbers                  | C++17    | [`src/forfun/add_two_numbers.cpp`](src/forfun/add_two_numbers.cpp)                                                         |
| Add Two Numbers (in C)           | C90      | [`src/forfun_c/add_two_numbers.c`](src/forfun_c/add_two_numbers.c)                                                         |
| Balanced Binary Tree             | C++23    | [`include/forfun/graph/balanced_binary_tree.hpp`](include/forfun/graph/balanced_binary_tree.hpp)                           |
| Best Time to Buy And Sell Stock  | C++20    | [`include/forfun/best_time_to_buy_and_sell_stock.hpp`](include/forfun/best_time_to_buy_and_sell_stock.hpp)                 |
| Binary Search                    | C++20    | [`include/forfun/search/binary_search.hpp`](include/forfun/search/binary_search.hpp)                                       |
| Breadth-First Search             | C++20    | [`include/forfun/graph/breadth_first_search.hpp`](include/forfun/graph/breadth_first_search.hpp)                             |
| Bubble Sort                      | C++20    | [`include/forfun/sorting/bubble_sort.hpp`](include/forfun/sorting/bubble_sort.hpp)                                         |
| Concatenation of Array           | C++17    | [`include/forfun/array_concatenation.hpp`](include/forfun/array_concatenation.hpp)                                         |
| Container with Most Water        | C++20    | [`include/forfun/container_with_most_water.hpp`](include/forfun/container_with_most_water.hpp)                             |
| Contains Duplicate               | C++20    | [`include/forfun/contains_duplicate.hpp`](include/forfun/contains_duplicate.hpp)                                           |
| Depth-First Search               | C++20    | [`include/forfun/graph/depth_first_search.hpp`](include/forfun/graph/depth_first_search.hpp)                                 |
| Encode and Decode Strings        | C++20    | [`src/forfun/encode_and_decode_strings.cpp`](src/forfun/encode_and_decode_strings.cpp)                                     |
| Evaluate Reverse Polish Notation | C++23    | [`include/forfun/evaluate_reverse_polish_notation.hpp`](include/forfun/evaluate_reverse_polish_notation.hpp)               |
| Factorial                        | C++23    | [`include/forfun/factorial.hpp`](include/forfun/factorial.hpp)                                                             |
| Fibonacci Sequence               | C++20    | [`include/forfun/fibonacci_sequence.hpp`](include/forfun/fibonacci_sequence.hpp)                                             |
| First Missing Positive           | C++20    | [`include/forfun/first_missing_positive.hpp`](include/forfun/first_missing_positive.hpp)                                     |
| Fizz Buzz                        | C++20    | [`include/forfun/fizzbuzz.hpp`](include/forfun/fizzbuzz.hpp)                                                                 |
| Forward List                     | C++20    | [`include/forfun/container/forward_list.hpp`](include/forfun/container/forward_list.hpp)                                   |
| Greatest Common Divisor          | C++20    | [`include/forfun/gcd.hpp`](include/forfun/gcd.hpp)                                                                         |
| Group Anagrams                   | C++23    | [`include/forfun/group_anagrams.hpp`](include/forfun/group_anagrams.hpp)                                                   |
| House Robber                     | C++20    | [`include/forfun/house_robber.hpp`](include/forfun/house_robber.hpp)                                                       |
| Insertion Sort                   | C++20    | [`include/forfun/sorting/insertion_sort.hpp`](include/forfun/sorting/insertion_sort.hpp)                                   |
| Last Stone Weight                | C++20    | [`include/forfun/last_stone_weight.hpp`](include/forfun/last_stone_weight.hpp)                                             |
| Least Recently Used (LRU) Cache  | C++20    | [`src/forfun/lru_cache.cpp`](src/forfun/lru_cache.cpp)                                                                     |
| Linked List                      | C++20    | [`include/forfun/container/list.hpp`](include/forfun/container/list.hpp)                                                   |
| List Bidirectional Iterator      | C++20    | [`include/forfun/container/internal/list_iterator.hpp`](include/forfun/container/internal/list_iterator.hpp)               |
| Longest Consecutive Sequence     | C++20    | [`include/forfun/longest_consecutive_sequence.hpp`](include/forfun/longest_consecutive_sequence.hpp)                       |
| Maximum Subarray                 | C++20    | [`include/forfun/maximum_subarray.hpp`](include/forfun/maximum_subarray.hpp)                                               |
| Meeting Rooms (I, II)            | C++20    | [`include/forfun/meeting_rooms.hpp`](include/forfun/meeting_rooms.hpp)                                                     |
| Move Zeroes                      | C++20    | [`include/forfun/move_zeroes.hpp`](include/forfun/move_zeroes.hpp)                                                         |
| Multiples of Three or Five       | C++17    | [`include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp`](include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp) |
| Nth Fibonacci Number             | C++20    | [`include/forfun/fibonacci.hpp`](include/forfun/fibonacci.hpp)                                                               |
| Number of Ships in a Rectangle   | C++20    | [`src/forfun/sonar.cpp`](src/forfun/sonar.cpp)                                                                             |
| Palindrome                       | C++20    | [`include/forfun/palindrome.hpp`](include/forfun/palindrome.hpp)                                                           |
| Palindrome (in C)                | C90      | [`src/forfun_c/palindrome.c`](src/forfun_c/palindrome.c)                                                                   |
| Palindromic Number               | C++20    | [`src/forfun/palindromic_number.cpp`](src/forfun/palindromic_number.cpp)                                                   |
| Primality Test                   | C++20    | [`include/forfun/primality.hpp`](include/forfun/primality.hpp)                                                             |
| Product of Array Except Self     | C++20    | [`include/forfun/product_except_self.hpp`](include/forfun/product_except_self.hpp)                                         |
| Quicksort                        | C++20    | [`include/forfun/sorting/quicksort.hpp`](include/forfun/sorting/quicksort.hpp)                                             |
| Set Matrix Zeroes                | C++20    | [`src/forfun/set_matrix_zeroes.cpp`](src/forfun/set_matrix_zeroes.cpp)                                                     |
| Squares of a Sorted Array        | C++20    | [`include/forfun/squares_sorted_array.hpp`](include/forfun/squares_sorted_array.hpp)                                       |
| Subsets                          | C++20    | [`include/forfun/graph/subsets.hpp`](include/forfun/graph/subsets.hpp)                                                     |
| Sums of Subarrays of Length K    | C++20    | [`include/forfun/sub_array_sums.hpp`](include/forfun/sub_array_sums.hpp)                                                   |
| Top K Frequent Elements          | C++23    | [`include/forfun/top_k_frequent_elements.hpp`](include/forfun/top_k_frequent_elements.hpp)                                 |
| Tower of Hanoi                   | C++20    | [`include/forfun/tower_of_hanoi.hpp`](include/forfun/tower_of_hanoi.hpp)                                                   |
| Trie                             | C++20    | [`include/forfun/trie.hpp`](include/forfun/trie.hpp)                                                                       |
| Two Sum (I, II)                  | C++23    | [`include/forfun/two_sum.hpp`](include/forfun/two_sum.hpp)                                                                 |
| Two-pass Boyer-Moore Majority    | C++20    | [`include/forfun/majority_element.hpp`](include/forfun/majority_element.hpp)                                               |
| Valid Anagram                    | C++20    | [`include/forfun/valid_anagram.hpp`](include/forfun/valid_anagram.hpp)                                                     |
| Valid Parentheses                | C++20    | [`src/forfun/valid_parentheses.cpp`](src/forfun/valid_parentheses.cpp)                                                     |
| Valid Sudoku                     | C++23    | [`include/forfun/valid_sudoku.hpp`](include/forfun/valid_sudoku.hpp)                                                       |

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
