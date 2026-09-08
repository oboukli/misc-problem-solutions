# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

function(forfun_unix_like_tool_properties target)
  set_target_properties(
    "${target}"
    PROPERTIES
      CXX_VISIBILITY_PRESET hidden
      VISIBILITY_INLINES_HIDDEN ON
  )
endfunction()

function(forfun_windows_tool_properties target)
  get_target_property(target_type "${target}" TYPE)
  if("${target_type}" STREQUAL "SHARED_LIBRARY")
    set_target_properties(
      "${target}"
      PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
  endif()
endfunction()

function(forfun_target_platform_properties target)
  if(WIN32)
    forfun_windows_tool_properties("${target}")
  endif()

  if(MSVC)
    include(cmake/MsvcSettings.cmake)

    forfun_msvc_properties("${target}")
  endif()

  if(MAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    forfun_unix_like_tool_properties("${target}")
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    include(cmake/ClangSettings.cmake)

    forfun_clang_properties("${target}")
  endif()

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      include(cmake/GccSettings.cmake)

      forfun_gcc_properties("${target}")
  endif()
endfunction()
