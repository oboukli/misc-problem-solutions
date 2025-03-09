# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

function(forfun_common_target_compile_options target)
  separate_arguments(
    FORFUN_COMMON_DEFINITIONS UNIX_COMMAND "${FORFUN_COMMON_DEFINITIONS}"
  )
  separate_arguments(
    FORFUN_COMMON_CFLAGS UNIX_COMMAND "${FORFUN_COMMON_CFLAGS}"
  )
  separate_arguments(
    FORFUN_COMMON_CXXFLAGS UNIX_COMMAND "${FORFUN_COMMON_CXXFLAGS}"
  )
  separate_arguments(
    FORFUN_COMMON_LINK_OPTIONS UNIX_COMMAND "${FORFUN_COMMON_LINK_OPTIONS}"
  )

  target_compile_definitions(
    ${target}
    PRIVATE ${FORFUN_COMMON_DEFINITIONS}
  )
  target_compile_options(
    ${target}
    PRIVATE $<$<COMPILE_LANGUAGE:C>:${FORFUN_COMMON_CFLAGS}>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${FORFUN_COMMON_CXXFLAGS}>
  )

  target_link_options(
    ${target}
    PRIVATE ${FORFUN_COMMON_LINK_OPTIONS}
  )
endfunction()
