# Developer notes

## Goals

This work aims at achieving:

- correctness (including semantic correctness of code, among other things)
- conformance to international standards (C, C++, Unicode, etc.)
- portability to at least three major platforms
- efficient and optimized runtime performance
- compatibility with at least four stable major compilers
- producing open and free (libre) deliverables

Non-goals include:

- Providing solutions in a language other than C and C++
- Supporting C standards aside from C90
- Supporting C++ standards before C++23
- Fast compilation
- Supporting non-latest compiler versions
- Optimizing for a specific platform, or processor architecture

## Architecture and design

### Dynamic memory allocation

Code that directly make use of dynamic allocation, i.e. by invoking `malloc` and
`new` directly, is isolated into build artifacts postfixed with `_experimental`
in the name.

The `forfun_c_experimental` static library, and the `test_driver_experimental`
executable utilize [mimalloc](https://github.com/microsoft/mimalloc).

### Exception safety-aware design

Functions and methods are annotated with the `noexcept` specifier where
applicable. In addition, special care is taken to order invocations of throwing
functions and methods to achieve the strongest exception safety possible.

An example can be seen in the
[`bucket_sort_based::top_frequent`](../include/forfun/top_k_frequent_elements.hpp)
strategy where a call to `std::sort` is delayed till after the
potentially-throwing `std::vector` constructor invocation.

## Internal checks

The design avoids fail-fast runtime guards in favor of performance and
composability.

### Static and shared libraries

All ForFun libraries can be built and linked as static or dynamic (shared), with
only the `forfun_c_experimental` library being an exception, as the latter is
meant to be statically linked. This is because the `forfun_c_experimental`
library defines, and makes available externally, the `g_forfun_mem` global state
variable.

### Thread safety

The code is not guaranteed to be thread-safe.

### Curiously recurring template pattern

An occurrence of the curiously recurring template pattern (CRTP), as a mixin
utilizing C++23's explicit object parameter, can be seen in
`list_iterator_helper`.

## Compiler standards

### Source code charset

All source code in this repository should be encoded in UTF-8 without byte order
mark (BOM). This is important to guarantee sources containing characters outside
the [standard C++ charset](https://en.cppreference.com/w/cpp/language/charset),
are compiled correctly. An example being the file `test/palindrome_test.cpp`.

For the MSVC compiler, the command-line option `/source-charset:utf-8`
should be passed, as seen in the `CMakePresets.json` file.

### Compiler support

The code is written in standards-compliant C90 and C++23 and is known to compile
with the following compilers.

- Apple Clang 26.2
- Clang 21.1
- GCC 14.2
- MSVC 19.43

The code passes most recommended compiler diagnostic options. Compiler options
are configured by means of CMake presets in `CMakePresets.json`.

See also the GitHub Actions CI configuration in
`.github/workflows/building-and-testing.yml`.

## Code annotations

The code attempts to use modern C++ attributes where supported, and it
experiments with the
[Guidelines Support Library (GSL)](https://github.com/microsoft/GSL).

## Code style

The code follows an opinionated modern C++ style, partially inspired by
Prettier, and managed with EditorConfig, Clang Format,
and the indent-rainbow VS Code extension.

Some notable style choices:

- Ubiquitous trailing return type declarations
- Ubiquitous brace-enclosed initialization
- Type qualifiers (e.g. `const`) on the right
- Lines restricted to eighty characters
- Indentation in multiples of four spaces (generally avoiding text alignment)
- Generous use of braces (on their own lines) and parentheses
- Generous amount of blank lines to separate code blocks
- Keyword-like forms of logical operators in concept declarations

## External dependency management

Beside the standard C++ and C libraries, the non-development build targets avoid
external dependencies. An exception is the `forfun_experimental` target, which
makes use of the Guidelines Support Library (GSL) and mimalloc.

Almost all external dependencies are managed with vcpkg in manifest mode.
The exceptions are Google FuzzTest, and vcpkg itself, which are manually managed
(cloned) with Git.

A list of vcpkg-managed dependencies can be seen in the manifest file
`vcpkg.json`.

## Performance benchmarking

Basic performance benchmarking is provided. The benchmarks mostly cover one
complexity case (e.g. worst-case complexity) and are not necessarily
statistically rigorous.

Benchmark code depends on an independent, free and open-source framework.

## Quality assurance

### Type safety and const-correctness

Initialization of variables follow the list-initialization syntax where
applicable.

Special care is taken to declare objects as `const` and `constexpr` where
applicable. This includes declaring pass-by-value parameters as `const`.

### Unit tests

The majority of runtime unit tests are hosted in the `test_driver` executable,
while the compile-time tests are compiled with the `static_test_driver`
one.

The scope of compile-time tests is limited to validating compile-time
constructs, e.g. C++20 concepts and `constexpr` symbols.

For code coverage instrumentation, non-compile-time tests should be evaluated at
runtime. Compile-time tests are isolated in own driver to mitigate their noise
in code coverage reports.

Test expected values should be immutable and immune to memory overwrites. Care
should be taken to initialize a test's expected value(s) after invoking the
function, method, or system under test (SUT), to help mitigate test expectations
being corrupted by, for example, memory overflows.

Unit tests for experimental code (mostly code utilizing manual memory
management) are hosted in the `test_driver_experimental` executable.

All Catch2 host targets support the Catch2 command-line options, such
as `--help` option. This means that tests can be filtered by tags. For example:

```bash
benchmark_driver '[sorting]'
```

### Code coverage

All code lines and branches are covered with tests, with the coverage percentage
target maintained at 100%.

Code coverage reports are generated with
[Clang Source-based Code Coverage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html).

A script for generating code coverage report with LLVM can be found at
`ci/generate_coverage_report.sh`. Usage example:

```bash
LLVM_ROOT='/usr/local/opt/llvm/' ./ci/generate_coverage_report.sh
```

### Compiler diagnostics

Clang's `implicit-conversion` flag is not enabled due to an issue in
libstdc++ 14.2.

### Dynamic analysis

All build targets are built with Clang and Xcode sanitizers, Microsoft STL
debugging checks. On Linux, the major targets are tested with Valgrind.

Clang's UndefinedBehaviorSanitizer runtime findings can be suppressed in
`ci/clang_ubsan_supp`.

See `CMakePresets.json` and CI configuration for more details.

### Fuzz tests

Fuzz tests for a selection of solutions are included under the `fuzz` directory,
all of which are developed within the Google FuzzTest and GTest frameworks.

It is not a goal of this work to have a fuzz test for each solution provided.

### Automated continuous integration

CI for building, testing (with the exception of fuzz testing), benchmarking,
dynamic analysis, and some static analysis, including security static analysis,
is hosted on
[GitHub Actions](https://github.com/oboukli/misc-problem-solutions/actions).

Fuzz testing, static analysis with Clang Tidy, and code style checking with
Clang Format are not enabled on GitHub Actions to avoid over-utilization of CI
resources.

## Leveraging artificial intelligence (AI)

Some configuration, e.g. that for CMake, may or may not leverage LLM tools
(ChatGPT and GitHub Copilot). However, the solutions themselves are not
AI-assisted.

In the hosting Git repository, any commit that contain AI-generated code or
AI-assisted configuration is labeled as AI-assisted in the body of the Git
commit message. In addition GitHub pull request containing AI-assisted commits
are labeled as such.

Some code or text in this repository may be reviewed with AI and not marked as
such if no AI-output makes its way to the final work.

Work under the `contrib/` directory may contain AI-generated code.

AI/LLM-based sources and tools may be utilized as learning and/or research media
by the author of this work.

This document is written by the author of the code (owner of the repository).
This document is not AI-generated.

## Build artifacts

| Artifact                      | Type                               |
| ---                           | ---                                |
| forfun                        | C++23 (static or shared) library   |
| forfun_graph                  | C++23 (static or shared) library   |
| forfun_search                 | C++23 (static or shared) library   |
| forfun_sorting                | C++23 (static or shared) library   |
| forfun_experimental           | C++23 (static or shared) library   |
| forfun_c                      | C90 (static or shared) library     |
| forfun_c_experimental         | C90 static library                 |
| test_driver                   | Executable Catch2 host             |
| test_driver_experimental      | Executable Catch2 host             |
| static_test_driver            | Executable Catch2 host             |
| benchmark_driver              | Executable Catch2 host             |
| benchmark_driver_experimental | Executable Catch2 host             |
| fuzzing_driver                | Executable FuzzTest host           |

## Problem-specific notes

## Contains duplicate

An interesting approach based on `std::adjacent_find` is provided.

A conjectured approach is to tailored sort algorithm that checks for duplicates
as it sorts, i.e, combine sort and search for consecutive duplicates.

### Encoding and decoding strings

The strategy does not implement error detection and error reporting.

### Integer division ceiling

This experiment demonstrates how good are modern compilers are. The
[benchmarks](../benchmark/common/math_benchmark.cpp) of function
`forfun::common::math::div_ceil` show no performance gains over utilizing casts,
floating-point division, and `std::ceil`.

### Meeting Rooms

The strategy of function `forfun::meeting_rooms::can_attend` relies on the input
being presorted. The function does not sort (and does not, in any other way,
mutate) the input. This is mainly to avoid the overhead of sorting in case the
input is already sorted, among other considerations.

Usage example:

```cpp
std::array intervals{
    forfun::meeting_rooms::interval{.start = 16, .end = 17},
    forfun::meeting_rooms::interval{.start = 14, .end = 15},
    forfun::meeting_rooms::interval{.start = 10, .end = 11},
    forfun::meeting_rooms::interval{.start = 13, .end = 14},
};

std::ranges::sort(
    intervals, {}, &forfun::meeting_rooms::interval::start
);

bool const result{forfun::meeting_rooms::can_attend(
    intervals.cbegin(), intervals.cend()
)};
```

### Subsets

The namespace `forfun::subsets` includes experimental custom allocators that
significantly improve the performance of the `explode_subsets` function by
preallocating the memory required for the result vectors.

See the [benchmark code](../benchmark/subsets_benchmark.cpp) and benchmarking
report for details.
