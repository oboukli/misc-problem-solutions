#!/usr/bin/env bash

# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

# Configuration section

IGNORE_FILENAME_REGEX="${IGNORE_FILENAME_REGEX:-benchmark|fuzz|test[\/\\].+}"

DRIVERS=(
  'test_driver'
  'test_driver_experimental'
)

EXECUTABLE_ARGS=(
  '--colour-mode' 'none'
  '--order' 'decl'
  '--out' '/dev/null'
  '--rng-seed' '0'
  '--verbosity' 'quiet'
)

PATH_PREFIX="${PATH_PREFIX:-$(pwd)/out/build/clang-coverage}"

REPORT_DIR="${REPORT_DIR:-$(pwd)/out/coverage/report}"
PROFDATA_DIR="${PROFDATA_DIR:-$(pwd)/out/coverage/profdata}"

# End of configuration section

if [[ -z "${LLVM_ROOT}" ]]; then
  printf 'Environment variable LLVM_ROOT must be set' 1>&2
  exit 1
fi

EXECUTABLE_EXTENSION="${EXECUTABLE_EXTENSION:-$(
  case "${OSTYPE}" in
    ('cygwin' | 'msys' | 'win32')
      printf '%s' '.exe'
      ;;
    (*)
      printf '%s' ''
      ;;
esac)}"

function profraw_file
{
  printf '%s/%s.profraw' "${PROFDATA_DIR}" "${1}"
}

function profdata_file
{
  printf '%s/%s.profdata' "${PROFDATA_DIR}" "${1}"
}

function driver_binary
{
  printf '%s/%s%s' "${PATH_PREFIX}" "${1}" "${EXECUTABLE_EXTENSION}"
}

function driver_crash_guard_file
{
  printf '%s/TEST_DRIVER_CRASHED__%s' "${PATH_PREFIX}" "${1}"
}

LLVM_PROFDATA="${LLVM_ROOT}/bin/llvm-profdata"
LLVM_COV="${LLVM_ROOT}/bin/llvm-cov"
LLVM_CXXFILT="${LLVM_ROOT}/bin/llvm-cxxfilt"
MKDIR=/usr/bin/mkdir
MV=/usr/bin/mv

"${MKDIR}" -p "${REPORT_DIR}"

index=1
for driver in "${DRIVERS[@]}";
do
  DRIVER_PROFRAW="$(profraw_file "${driver}")"
  DRIVER_BINARY="$(driver_binary "${driver}")"
  DRIVER_CRASH_GUARD_FILE="$(driver_crash_guard_file "${driver}")"

  LLVM_PROFILE_FILE="${DRIVER_PROFRAW}" \
    "${DRIVER_BINARY}" \
    "${EXECUTABLE_ARGS[@]}" \
    --premature-exit-guard-file "${DRIVER_CRASH_GUARD_FILE}" \
    1>/dev/null

  {
    if [ -f "${DRIVER_CRASH_GUARD_FILE}" ]; then
      printf 'A test driver crashed: "%s"' "${DRIVER_BINARY}" 1>&2
      exit 1
    fi
  }

  MERGED_PROFDATA="$(profdata_file "${driver}")"

  "${LLVM_PROFDATA}" merge \
    --sparse \
    --output "${MERGED_PROFDATA}" \
    "${DRIVER_PROFRAW}"

  "${LLVM_COV}" show \
    --format=html \
    --ignore-filename-regex="${IGNORE_FILENAME_REGEX}" \
    --instr-profile="${MERGED_PROFDATA}" \
    --output-dir="${REPORT_DIR}" \
    --show-branches=count \
    --show-mcdc \
    --show-expansions \
    --show-instantiation-summary \
    --show-line-counts-or-regions \
    --use-color \
    --Xdemangler="${LLVM_CXXFILT}" \
    --Xdemangler=--no-strip-underscore \
    --Xdemangler=--types \
    "${DRIVER_BINARY}"

  REPORT_FILE="$(
    printf '%s/index_%02d.html' "${REPORT_DIR}" "${index}"
  )"

  "${MV}" \
    "${REPORT_DIR}/index.html" \
    "${REPORT_FILE}"

  ((index++))
done
