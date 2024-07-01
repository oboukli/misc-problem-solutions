# Developer notes

## Source code charset

All source code in this repository should be encoded in
UTF-8 without byte order mark (BOM). This is important to guarantee sources
containing characters outside the
[standard C++ charset](https://en.cppreference.com/w/cpp/language/charset),
are compiled correctly. An example is `test/palindrome_test.cpp`.

For the MSVC compiler, the command-line option `/source-charset:utf-8`
should be passed, as seen in the `CMakePresets.json` file.
