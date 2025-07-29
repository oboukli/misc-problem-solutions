#!/usr/bin/env bash

# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

CLANG_FORMAT="${LLVM_ROOT}/bin/clang-format"

printf 'Formatting with %s\n' "$("${CLANG_FORMAT}" --version)"

WORK_DIR="$(pwd)"

CODE_DIRS=(
  "${WORK_DIR}/benchmark"
  "${WORK_DIR}/fuzz"
  "${WORK_DIR}/include"
  "${WORK_DIR}/src"
  "${WORK_DIR}/test"
)

for code_dir in "${CODE_DIRS[@]}";
do
  (
    cd "${code_dir}"
    find . -regex '.+\.\(cpp\|c\|h\|hpp\)$' \
    -exec "${CLANG_FORMAT}" -style=file -i {} \;
  )

  printf '.'
done
printf '\n'

wait

printf 'Done\n'
