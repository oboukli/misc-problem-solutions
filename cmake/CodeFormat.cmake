# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

find_program(
  CLANG_FORMAT_EXE
  NAMES
    clang-format
)

if(NOT CLANG_FORMAT_EXE)
  message(NOTICE "Clang Format not found. Skipping code format targets.")
  return()
endif()

set(support_folder "support")

cmake_path(
  APPEND support_folder
    "per_target"
  OUTPUT_VARIABLE support_per_target_folder
)

add_custom_target(
  format_code
  COMMENT "Formatting all code"
)
set_target_properties(
  format_code
  PROPERTIES
    FOLDER "${support_folder}"
)

add_custom_target(
  format_check
  COMMENT "Checking code formatting"
)
set_target_properties(
  format_check
  PROPERTIES
    FOLDER "${support_folder}"
)

block()
  set(
    file_extensions
    .c
    .cpp
    .cppm
    .h
    .hpp
  )

  set(
    supported_target_types
    EXECUTABLE
    INTERFACE_LIBRARY
    MODULE_LIBRARY
    SHARED_LIBRARY
    STATIC_LIBRARY
  )

  function(clang_format_target target)
    get_target_property(type "${target}" TYPE)

    if(NOT type IN_LIST supported_target_types)
      return()
    endif()

    set(target_files "")

    get_target_property(header_files "${target}" HEADER_SET)
    if(header_files)
      list(APPEND target_files ${header_files})
    endif()

    get_target_property(source_files "${target}" SOURCES)
    if(source_files)
      list(APPEND target_files ${source_files})
    endif()

    list(FILTER target_files EXCLUDE REGEX [[\$<]])

    foreach(file IN LISTS target_files)
      get_filename_component(ext "${file}" EXT)
      if(NOT ext IN_LIST file_extensions)
        list(REMOVE_ITEM target_files file)
        continue()
      endif()

      get_filename_component(file "${file}" ABSOLUTE)
      if(EXISTS "${file}")
        get_source_file_property(is_generated "${file}" GENERATED)
        if(is_generated)
          list(REMOVE_ITEM target_files file)
          continue()
        endif()
      endif()
    endforeach()

    if(NOT target_files)
      return()
    endif()

    list(REMOVE_DUPLICATES target_files)

    set(fmt_target "format_${target}")
    set(check_target "format_check_${target}")

    add_custom_target(
      "${fmt_target}"
      COMMAND
        "${CLANG_FORMAT_EXE}"
        --fail-on-incomplete-format
        -i
        --style=file
        ${target_files}
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      COMMENT "Formatting ${target}"
      VERBATIM
    )
    set_target_properties(
      "${fmt_target}"
      PROPERTIES
        FOLDER "${support_per_target_folder}"
    )

    add_custom_target(
      "${check_target}"
      COMMAND
        "${CLANG_FORMAT_EXE}"
        --dry-run
        --fail-on-incomplete-format
        --style=file
        --Werror
        ${target_files}
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      COMMENT "Checking format ${target}"
      VERBATIM
    )
    set_target_properties(
      "${check_target}"
      PROPERTIES
        FOLDER "${support_per_target_folder}"
    )

    add_dependencies(format_code "${fmt_target}")
    add_dependencies(format_check "${check_target}")
  endfunction()

  get_directory_property(targets BUILDSYSTEM_TARGETS)

  foreach(target IN LISTS targets)
    clang_format_target("${target}")
  endforeach()
endblock()
