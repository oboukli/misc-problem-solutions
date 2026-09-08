# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(config_input_file "ProjectConfigInput.cmake.in")

cmake_path(
  APPEND_STRING PROJECT_NAME
    "Config.cmake"
  OUTPUT_VARIABLE config_file
)

cmake_path(
  APPEND_STRING PROJECT_NAME
    "ConfigVersion.cmake"
  OUTPUT_VARIABLE config_version_file
)

cmake_path(
  APPEND_STRING PROJECT_NAME
    "Targets"
  OUTPUT_VARIABLE export_set_name
)

cmake_path(
  APPEND CMAKE_CURRENT_BINARY_DIR
    "${config_file}"
  OUTPUT_VARIABLE config_file_path
)

cmake_path(
  APPEND CMAKE_CURRENT_BINARY_DIR
    "${config_version_file}"
  OUTPUT_VARIABLE config_version_file_path
)

cmake_path(
  APPEND CMAKE_CURRENT_SOURCE_DIR
    "cmake"
    "${config_input_file}"
  OUTPUT_VARIABLE config_input_file_path
)

cmake_path(
  APPEND CMAKE_INSTALL_LIBDIR
    "cmake"
    "${PROJECT_NAME}"
  OUTPUT_VARIABLE install_destination
)

configure_package_config_file(
  "${config_input_file_path}"
  "${config_file_path}"
  INSTALL_DESTINATION "${install_destination}"
)

write_basic_package_version_file(
  "${config_version_file_path}"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion
)

install(
  TARGETS
    forfun_common
    forfun_core
    forfun_core_c
    forfun_experimental
    forfun_experimental_c
    forfun_graph
    forfun_lock_free
    forfun_math
    forfun_search
    forfun_sorting
  EXPORT "${export_set_name}"
  FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  EXPORT "${export_set_name}"
  FILE "${export_set_name}.cmake"
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION "${install_destination}"
)

install(
  FILES
    "${config_file_path}"
    "${config_version_file_path}"
  DESTINATION "${install_destination}"
)

install(
  FILES "${PROJECT_SOURCE_DIR}/LICENSE"
  TYPE DOC
)
