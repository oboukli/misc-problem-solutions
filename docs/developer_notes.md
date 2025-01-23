# Developer notes

## Source code charset

All source code in this repository should be encoded in
UTF-8 without byte order mark (BOM). This is important to guarantee sources
containing characters outside the
[standard C++ charset](https://en.cppreference.com/w/cpp/language/charset),
are compiled correctly. An example is `test/palindrome_test.cpp`.

For the MSVC compiler, the command-line option `/source-charset:utf-8`
should be passed, as seen in the `CMakePresets.json` file.

## Exception safety-aware design

Functions and methods are annotated with the `noexcept` specifier where
applicable. In addition, special care is taken to order calls to throwing
functions and methods to achieve the strongest exception safety possible.

An example can be seen in the
[`bucket_sort_based::top_frequent`](../include/forfun/top_k_frequent_elements.hpp)
strategy where a call to `std::sort` is delayed till after the possibly throwing
`std::vector` constructor.

## Curiously recurring template pattern

An occurrence of the curiously recurring template pattern (CRTP), as a mixin
utilizing C++23's explicit object parameter, can be seen in
`list_iterator_helper`.

## Problem-specific notes

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
