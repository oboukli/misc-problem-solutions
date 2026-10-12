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
  'test_driver_lock_free'
)

EXECUTABLE_ARGS=(
  '--colour-mode' 'none'
  '--order' 'decl'
  '--out' '/dev/null'
  '--rng-seed' '0'
  '--verbosity' 'quiet'
)

PATH_PREFIX="${PATH_PREFIX:-$(pwd)/out/build/code-coverage}"

REPORT_DIR="${REPORT_DIR:-$(pwd)/out/coverage/report}"
PROFDATA_DIR="${PROFDATA_DIR:-$(pwd)/out/coverage/profdata}"
COVERAGE_FILE="${COVERAGE_FILE:-$(pwd)/out/coverage/cobertura.xml}"

# End of configuration section

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

if [[ -n "${LLVM_ROOT}" ]]; then
  LLVM_PROFDATA="${LLVM_ROOT}/bin/llvm-profdata"
  LLVM_COV="${LLVM_ROOT}/bin/llvm-cov"
  LLVM_CXXFILT="${LLVM_ROOT}/bin/llvm-cxxfilt"
else
  LLVM_PROFDATA="$(command -v llvm-profdata || true)"
  LLVM_COV="$(command -v llvm-cov || true)"
  LLVM_CXXFILT="$(command -v llvm-cxxfilt || true)"

  if [[ -z "${LLVM_PROFDATA}" || -z "${LLVM_COV}" || -z "${LLVM_CXXFILT}" ]]; then
    printf 'LLVM_ROOT is unset and LLVM tools were not found in PATH\n' 1>&2
    exit 1
  fi
fi

MKDIR=/usr/bin/mkdir
MV=/usr/bin/mv

"${MKDIR}" -p "${REPORT_DIR}" "${PROFDATA_DIR}" "$(dirname "${COVERAGE_FILE}")"

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

COMBINED_PROFDATA="$(profdata_file combined)"
LCOV_FILE="${PROFDATA_DIR}/combined.info"

"${LLVM_PROFDATA}" merge \
  --sparse \
  --output "${COMBINED_PROFDATA}" \
  "$(profraw_file test_driver)" \
  "$(profraw_file test_driver_experimental)" \
  "$(profraw_file test_driver_lock_free)"

"${LLVM_COV}" export \
  --format=lcov \
  --ignore-filename-regex="${IGNORE_FILENAME_REGEX}" \
  --instr-profile="${COMBINED_PROFDATA}" \
  "$(driver_binary test_driver)" \
  -object "$(driver_binary test_driver_experimental)" \
  -object "$(driver_binary test_driver_lock_free)" \
  > "${LCOV_FILE}"

if command -v lcov_cobertura >/dev/null 2>&1; then
  lcov_cobertura \
    "${LCOV_FILE}" \
    --base-dir "$(pwd)" \
    --output "${COVERAGE_FILE}"
else
  printf 'Skipping Cobertura XML conversion: lcov_cobertura is not installed\n' >&2
fi
