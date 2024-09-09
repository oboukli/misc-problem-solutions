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

| Problem                          | Standard | Source                                                       |
| ---                              | ---      | ---                                                          |
| Binary search                    | C++20    | `include/forfun/search/binary_search.hpp`                    |
| Breadth-first search             | C++20    | `include/forfun/graph/breadth_first_search.hpp`              |
| Bubble sort                      | C++20    | `include/forfun/sorting/bubble_sort.hpp`                     |
| Concatenation of array           | C++17    | `include/forfun/array_concatenation.hpp`                     |
| Contains duplicate               | C++20    | `include/forfun/contains_duplicate.hpp`                      |
| Depth-first search               | C++20    | `include/forfun/graph/depth_first_search.hpp`                |
| Evaluate reverse polish notation | C++20    | `include/forfun/evaluate_reverse_polish_notation.hpp`        |
| Factorial                        | C++23    | `include/forfun/factorial.hpp`                               |
| Fibonacci sequence               | C++20    | `include/forfun/fibonacci_sequence.hpp`                      |
| First missing positive           | C++20    | `include/forfun/first_missing_positive.hpp`                  |
| Fizz buzz                        | C++17    | `src/forfun/fizzbuzz.cpp`                                    |
| Greatest common divisor          | C++17    | `include/forfun/gcd.hpp`                                     |
| Insertion sort                   | C++20    | `include/forfun/sorting/insertion_sort.hpp`                  |
| Least recently used (LRU) cache  | C++20    | `src/forfun/lru_cache.cpp`                                   |
| Linked list                      | C++20    | `include/forfun/container/list.hpp`                          |
| List bidirectional iterator      | C++20    | `include/forfun/container/internal/list_iterator.hpp`        |
| Move zeroes                      | C++20    | `include/forfun/move_zeroes.hpp`                             |
| Multiples of three or five       | C++17    | `include/forfun/project_euler/p0001_multiples_of_3_or_5.hpp` |
| Nth Fibonacci number             | C++20    | `include/forfun/fibonacci.hpp`                               |
| Number of ships in a rectangle   | C++20    | `src/forfun/sonar.cpp`                                       |
| Palindrome                       | C++20    | `include/forfun/palindrome.hpp`                              |
| Palindrome (in C)                | C90      | `src/forfun_c/palindrome.c`                                  |
| Palindromic number               | C++20    | `src/forfun/palindromic_number.cpp`                          |
| Primality test                   | C++20    | `include/forfun/primality.hpp`                               |
| Product of array except self     | C++20    | `include/forfun/product_except_self.hpp`                     |
| Quicksort                        | C++20    | `include/forfun/sorting/quicksort.hpp`                       |
| Set matrix zeroes                | C++17    | `src/forfun/set_matrix_zeroes.cpp`                           |
| Sums of subarrays of length k    | C++20    | `include/forfun/sub_array_sums.hpp`                          |
| Tower of Hanoi                   | C++20    | `include/forfun/tower_of_hanoi.hpp`                          |
| Trie                             | C++20    | `include/forfun/trie.hpp`                                    |
| Two sum                          | C++20    | `include/forfun/two_sum.hpp`                                 |
| Two-pass Boyer-Moore majority    | C++20    | `include/forfun/majority_element.hpp`                        |
| Valid anagram                    | C++20    | `include/forfun/valid_anagram.hpp`                           |
| Valid parentheses                | C++20    | `src/forfun/valid_parentheses.cpp`                           |

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
