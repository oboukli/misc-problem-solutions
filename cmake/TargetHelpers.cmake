# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(cmake/CompilerSettings.cmake)

function(forfun_target_standards target)
  target_compile_features("${target}" PUBLIC c_std_90)
  target_compile_features("${target}" PUBLIC cxx_std_23)

  set_target_properties(
    "${target}"
    PROPERTIES
      C_EXTENSIONS OFF
      C_STANDARD 90
      C_STANDARD_REQUIRED ON
      CXX_EXTENSIONS OFF
      CXX_STANDARD_REQUIRED ON
  )
endfunction()

function(forfun_target_ide_folder target path)
  cmake_path(NORMAL_PATH path OUTPUT_VARIABLE normalized)
  cmake_path(GET normalized FILENAME name)

  if("${name}" STREQUAL "src")
    set(folder_name "")
  else()
    set(folder_name "${name}")
  endif()

  set_target_properties(
    "${target}"
    PROPERTIES
      FOLDER "${folder_name}"
  )
endfunction()

# forfun_target_config(
#   <target>
#   [HEADERS_DIR <headers-dir>]
#   [SOURCES_DIR <sources-dir>]
#   [HEADERS <header>...]
#   [SOURCES <source>...]
# )
function(forfun_target_config target)
  cmake_parse_arguments(
    PARSE_ARGV 1
    arg
    ""
    "HEADERS_DIR;SOURCES_DIR"
    "HEADERS;SOURCES"
  )

  if(arg_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR
      "forfun_target_config: Unrecognized arguments: ${arg_UNPARSED_ARGUMENTS}."
    )
  endif()

  if(NOT TARGET "${target}")
    message(
      FATAL_ERROR
      "forfun_target_config: target \"${target}\" does not exist."
    )
  endif()

  if(NOT DEFINED arg_HEADERS_DIR)
    set(arg_HEADERS_DIR "include")
  endif()

  if(NOT DEFINED arg_SOURCES_DIR)
    set(arg_SOURCES_DIR "src")
  endif()

  forfun_target_ide_folder("${target}" "${arg_SOURCES_DIR}")

  get_target_property(target_type "${target}" TYPE)
  if(target_type STREQUAL "INTERFACE_LIBRARY")
    if(arg_SOURCES)
      message(
        FATAL_ERROR
        "forfun_target_config: \"${target}\" is an INTERFACE library and cannot have SOURCES."
      )
    endif()

    set(scope INTERFACE)
  else()
    set(scope PUBLIC)

    if(target_type STREQUAL "LIBRARY")
      add_library("${PROJECT_NAME}::${target}" ALIAS "${target}")
    endif()

    if(
      target_type STREQUAL "STATIC_LIBRARY"
      OR target_type STREQUAL "SHARED_LIBRARY"
      OR target_type STREQUAL "MODULE_LIBRARY"
      OR target_type STREQUAL "INTERFACE_LIBRARY"
      OR target_type STREQUAL "OBJECT_LIBRARY"
    )
      add_library("${PROJECT_NAME}::${target}" ALIAS "${target}")
    endif()
  endif()

  forfun_target_standards("${target}")

  forfun_target_platform_properties("${target}")

  set(include_dir "")
  set(src_dir "")

  if(arg_HEADERS)
    cmake_path(
      APPEND include_dir
      "${CMAKE_CURRENT_SOURCE_DIR}"
      "${arg_HEADERS_DIR}"
    )
  endif()

  cmake_path(
    APPEND src_dir
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${arg_SOURCES_DIR}"
  )

  target_include_directories(
    "${target}"
    ${scope}
      "$<BUILD_INTERFACE:${include_dir}>"
      "$<INSTALL_INTERFACE:include>"
  )

  if(arg_HEADERS)
    list(
      TRANSFORM arg_HEADERS
      PREPEND "${include_dir}/"
      OUTPUT_VARIABLE abs_headers
    )

    target_sources(
      "${target}"
      ${scope}
      FILE_SET HEADERS
      BASE_DIRS "${include_dir}"
      FILES
        ${abs_headers}
    )
    source_group(
      TREE "${include_dir}"
      PREFIX "Header files"
      FILES
        ${abs_headers}
    )
  endif()

  if(arg_SOURCES)
    list(
      TRANSFORM arg_SOURCES
      PREPEND "${src_dir}/"
      OUTPUT_VARIABLE abs_sources
    )

    target_sources(
      "${target}"
      PRIVATE ${abs_sources}
    )
    source_group(
      TREE "${src_dir}"
      PREFIX "Source files"
      FILES ${abs_sources}
    )
  endif()
endfunction()
