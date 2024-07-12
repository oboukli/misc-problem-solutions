# Solutions to miscellaneous coding problems in C/C++

This is a repository of modern coding showcases and solutions to various
programming problems, written in C90, C++17, C++20, and C++23.

## Technical showcases

The following is a partial list of standards, practices, software,
and ideas leveraged by this project:

- C (standard C90)
- C++ (standard C++17, C++20, and C++23)
- C++ STL
- Strongly-typed approach, leveraging C++ templates and concepts
- Const correctness where applicable--except for fields
- Functional programming
- Strict compilation
- Static analysis with Clang Tidy and Microsoft C++ Code Analysis
- Dynamic analysis
- CMake
- Clean Git history and configuration
- Extensive testing using Catch2 and CTest
- Development dependency management using vcpkg
- Opinionated Clang Format configuration
- Conventional Commits
- GitHub Actions CI
- Benchmarking using nanobench
- Microsoft DevSkim
- EditorConfig
- Markdown
- Diagraming with Mermaid

## Index

| Problem                         | Standard | Source                                                       |
| ---                             | ---      | ---                                                          |
| Binary search                   | C++20    | `include/forfun/search/binary_search.hpp`                    |
| Breadth-first search            | C++20    | `include/forfun/graph/breadth_first_search.hpp`              |
| Bubble sort                     | C++20    | `include/forfun/sorting/bubble_sort.cpp`                     |
| Contains duplicate              | C++20    | `include/forfun/contains_duplicate.cpp`                      |
| Depth-first search              | C++20    | `include/forfun/graph/depth_first_search.hpp`                |
| Factorial                       | C++23    | `include/forfun/factorial.cpp`                               |
| Fibonacci sequence              | C++20    | `include/forfun/fibonacci_sequence.cpp`                      |
| First missing positive          | C++20    | `include/forfun/first_missing_positive.cpp`                  |
| Fizz buzz                       | C++17    | `src/forfun/fizzbuzz.cpp`                                    |
| Greatest common divisor         | C++17    | `include/forfun/gcd.cpp`                                     |
| Insertion sort                  | C++20    | `include/forfun/sorting/insertion_sort.cpp`                  |
| Least recently used (LRU) cache | C++20    | `src/forfun/lru_cache.cpp`                                   |
| Move zeroes                     | C++20    | `include/forfun/move_zeroes.cpp`                             |
| Multiples of three or five      | C++17    | `include/forfun/project_euler/p0001_multiples_of_3_or_5.cpp` |
| Nth Fibonacci number            | C++20    | `include/forfun/fibonacci.cpp`                               |
| Number of ships in a rectangle  | C++20    | `src/forfun/sonar.cpp`                                       |
| Palindrome                      | C++17    | `include/forfun/palindrome.cpp`                              |
| Palindrome (in C)               | C90      | `src/forfun_c/palindrome.c`                                  |
| Palindromic number              | C++20    | `src/forfun/palindromic_number.cpp`                          |
| Primality test                  | C++20    | `include/forfun/primality.hpp`                               |
| Product except self             | C++20    | `include/forfun/product_except_self.cpp`                     |
| Quicksort                       | C++20    | `include/forfun/sorting/quicksort.cpp`                       |
| Set matrix zeroes               | C++17    | `src/forfun/set_matrix_zeroes.cpp`                           |
| Sub array sums                  | C++20    | `include/forfun/sub_array_sums.cpp`                          |
| Tower of Hanoi                  | C++20    | `include/forfun/tower_of_hanoi.hpp`                          |
| Trie                            | C++20    | `include/forfun/trie.cpp`                                    |
| Two sum                         | C++20    | `include/forfun/two_sum.cpp`                                 |
| Two-pass Boyer-Moore majority   | C++20    | `include/forfun/majority_element.hpp`                        |

## Disclaimer

The provided attempted solutions are not guaranteed to be correct, safe,
secure, optimal, or suitable for use in production. The code and coding style
may, or may not, follow best practice guidelines.

## License

### Problem licenses

Problem copyrights are reserved to their respective owners.

### Solution licenses

Solutions are released under an [MIT-style license](LICENSE).
Copyright © Omar Boukli-Hacene. All rights reserved.

SPDX license identifier: MIT.
