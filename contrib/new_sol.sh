#!/usr/bin/env bash

# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

function usage {
    echo "Usage: $0 <name> [prefix]"
    echo
    echo 'Example:'
    echo "$0 'Binary search' search"
    exit 1
}

if [ $# -eq 0 ]; then
    usage
fi

SNAKE_NAME=$(echo "${1}" | tr '[:upper:][:blank:]' '[:lower:]_')
KEBAB_NAME=$(echo "${1}" | tr '[:upper:][:blank:]' '[:lower:]-')
PREFIX="${2:+${2}/}"

PATH_PREFIX=$(pwd)

HEADER_DIR="include/forfun/${PREFIX}"
SRC_DIR="src/forfun/${PREFIX}"
TEST_DIR="test/${PREFIX}"
BENCHMARK_DIR="benchmark/${PREFIX}"

HEADER_FILE="include/forfun/${PREFIX}${SNAKE_NAME}.hpp"
SRC_FILE="src/forfun/${PREFIX}${SNAKE_NAME}.cpp"
TEST_FILE="test/${PREFIX}${SNAKE_NAME}_test.cpp"
BENCHMARK_FILE="benchmark/${PREFIX}${SNAKE_NAME}_benchmark.cpp"

mkdir -p "$PATH_PREFIX/$HEADER_DIR"
mkdir -p "$PATH_PREFIX/$SRC_DIR"
mkdir -p "$PATH_PREFIX/$TEST_DIR"
mkdir -p "$PATH_PREFIX/$BENCHMARK_DIR"

# New git branch
echo "git switch -c feature/$KEBAB_NAME"
echo

# Markdown for README
echo "| $1 | C++20    | \`$HEADER_FILE\` |"
echo

touch "$PATH_PREFIX/$HEADER_FILE"
echo \"$HEADER_FILE\"

touch "$PATH_PREFIX/$SRC_FILE"
echo \"$SRC_FILE\"

touch "$PATH_PREFIX/$TEST_FILE"
echo \"$TEST_FILE\"

touch "$PATH_PREFIX/$BENCHMARK_FILE"
echo \"$BENCHMARK_FILE\"
