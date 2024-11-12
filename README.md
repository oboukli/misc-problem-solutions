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
- Const correctness where applicable--except for fields
- Functional programming
- Strict standard conformance and strict compilation rules
- Static analysis with Clang Tidy and Microsoft C++ Code Analysis
- Dynamic analysis
- LLVM-based sanitizer tools
- CMake
- Clean Git history and configuration
- Extensive testing using Catch2 and CTest
- Development dependency management using vcpkg
- Own opinionated Clang Format configuration
- Conventional Commits
- GitHub Actions CI
- Benchmarking using nanobench
- Microsoft DevSkim
- EditorConfig
- Markdown
- Diagraming with Mermaid

## Index

| Problem                          | Standard | Source                                                                                                                     |
| ---                              | ---      | ---                                                                                                                        |
| Add two numbers                  | C++17    | [`src/forfun/add_two_numbers.cpp`](src/forfun/add_two_numbers.cpp)                                                         |
| Add two numbers (in C)           | C90      | [`src/forfun_c/add_two_numbers.c`](src/forfun_c/add_two_numbers.c)                                                         |
| Balanced binary tree             | C++17    | [`include/forfun/graph/balanced_binary_tree.hpp`](include/forfun/graph/balanced_binary_tree.hpp)                           |
| Best time to buy and sell stock  | C++20    | [`include/forfun/best_time_to_buy_and_sell_stock.hpp`](include/forfun/best_time_to_buy_and_sell_stock.hpp)                 |
| Binary search                    | C++20    | [`include/forfun/search/binary_search.hpp`](include/forfun/search/binary_search.hpp)                                       |
| Breadth-first search             | C++20    | [`include/forfun/graph/breadth_first_search.hpp`](include/forfun/graph/breadth_first_search.hpp)                           |
| Bubble sort                      | C++20    | [`include/forfun/sorting/bubble_sort.hpp`](include/forfun/sorting/bubble_sort.hpp)                                         |
| Concatenation of array           | C++17    | [`include/forfun/array_concatenation.hpp`](include/forfun/array_concatenation.hpp)                                         |
| Contains duplicate               | C++20    | [`include/forfun/contains_duplicate.hpp`](include/forfun/contains_duplicate.hpp)                                           |
| Depth-first search               | C++20    | [`include/forfun/graph/depth_first_search.hpp`](include/forfun/graph/depth_first_search.hpp)                               |
| Evaluate reverse polish notation | C++23    | [`include/forfun/evaluate_reverse_polish_notation.hpp`](include/forfun/evaluate_reverse_polish_notation.hpp)               |
| Factorial                        | C++23    | [`include/forfun/factorial.hpp`](include/forfun/factorial.hpp)                                                             |
| Fibonacci sequence               | C++20    | [`include/forfun/fibonacci_sequence.hpp`](include/forfun/fibonacci_sequence.hpp)                                           |
| First missing positive           | C++20    | [`include/forfun/first_missing_positive.hpp`](include/forfun/first_missing_positive.hpp)                                   |
| Fizz buzz                        | C++20    | [`include/forfun/fizzbuzz.hpp`](include/forfun/fizzbuzz.hpp)                                                               |
| Forward list                     | C++20    | [`include/forfun/container/forward_list.hpp`](include/forfun/container/forward_list.hpp)                                   |
| Greatest common divisor          | C++17    | [`include/forfun/gcd.hpp`](include/forfun/gcd.hpp)                                                                         |
| Insertion sort                   | C++20    | [`include/forfun/sorting/insertion_sort.hpp`](include/forfun/sorting/insertion_sort.hpp)                                   |
| Last stone weight                | C++20    | [`include/forfun/last_stone_weight.hpp`](include/forfun/last_stone_weight.hpp)                                             |
| Least recently used (LRU) cache  | C++20    | [`src/forfun/lru_cache.cpp`](src/forfun/lru_cache.cpp)                                                                     |
| Linked list                      | C++20    | [`include/forfun/container/list.hpp`](include/forfun/container/list.hpp)                                                   |
| List bidirectional iterator      | C++20    | [`include/forfun/container/internal/list_iterator.hpp`](include/forfun/container/internal/list_iterator.hpp)               |
| Maximum subarray                 | C++20    | [`include/forfun/maximum_subarray.hpp`](include/forfun/maximum_subarray.hpp)                                               |
| Meeting rooms                    | C++20    | [`include/forfun/meeting_rooms.hpp`](include/forfun/meeting_rooms.hpp)                                                     |
| Move zeroes                      | C++20    | [`include/forfun/move_zeroes.hpp`](include/forfun/move_zeroes.hpp)                                                         |
| Multiples of three or five       | C++17    | [`include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp`](include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp) |
| Nth Fibonacci number             | C++20    | [`include/forfun/fibonacci.hpp`](include/forfun/fibonacci.hpp)                                                             |
| Number of ships in a rectangle   | C++20    | [`src/forfun/sonar.cpp`](src/forfun/sonar.cpp)                                                                             |
| Palindrome                       | C++20    | [`include/forfun/palindrome.hpp`](include/forfun/palindrome.hpp)                                                           |
| Palindrome (in C)                | C90      | [`src/forfun_c/palindrome.c`](src/forfun_c/palindrome.c)                                                                   |
| Palindromic number               | C++20    | [`src/forfun/palindromic_number.cpp`](src/forfun/palindromic_number.cpp)                                                   |
| Primality test                   | C++20    | [`include/forfun/primality.hpp`](include/forfun/primality.hpp)                                                             |
| Product of array except self     | C++20    | [`include/forfun/product_except_self.hpp`](include/forfun/product_except_self.hpp)                                         |
| Quicksort                        | C++20    | [`include/forfun/sorting/quicksort.hpp`](include/forfun/sorting/quicksort.hpp)                                             |
| Set matrix zeroes                | C++17    | [`src/forfun/set_matrix_zeroes.cpp`](src/forfun/set_matrix_zeroes.cpp)                                                     |
| Subsets                          | C++20    | [`include/forfun/graph/subsets.hpp`](include/forfun/graph/subsets.hpp)                                                     |
| Sums of subarrays of length k    | C++20    | [`include/forfun/sub_array_sums.hpp`](include/forfun/sub_array_sums.hpp)                                                   |
| Top K frequent elements          | C++23    | [`include/forfun/top_k_frequent_elements.hpp`](include/forfun/top_k_frequent_elements.hpp)                                 |
| Tower of Hanoi                   | C++20    | [`include/forfun/tower_of_hanoi.hpp`](include/forfun/tower_of_hanoi.hpp)                                                   |
| Trie                             | C++20    | [`include/forfun/trie.hpp`](include/forfun/trie.hpp)                                                                       |
| Two sum                          | C++20    | [`include/forfun/two_sum.hpp`](include/forfun/two_sum.hpp)                                                                 |
| Two-pass Boyer-Moore majority    | C++20    | [`include/forfun/majority_element.hpp`](include/forfun/majority_element.hpp)                                               |
| Valid anagram                    | C++20    | [`include/forfun/valid_anagram.hpp`](include/forfun/valid_anagram.hpp)                                                     |
| Valid parentheses                | C++20    | [`src/forfun/valid_parentheses.cpp`](src/forfun/valid_parentheses.cpp)                                                     |

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
