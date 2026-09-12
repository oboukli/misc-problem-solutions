# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

include_guard(GLOBAL)

function(forfun_msvc_properties target)
  target_compile_options(
    "${target}"
    PRIVATE
      $<$<COMPILE_LANG_AND_ID:C,MSVC>:
        /permissive-
        /utf-8
        /Zc:enumTypes
        /Zc:inline
        /Zc:preprocessor
      >
      $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:
        /EHsc
        /permissive-
        /utf-8
        /Zc:__cplusplus
        /Zc:checkGwOdr
        /Zc:enumTypes
        /Zc:inline
        /Zc:preprocessor
        /Zc:templateScope
        /Zc:throwingNew
      >
  )

  if(FORFUN_ENABLE_STRICT_COMPILATION)
    target_compile_options(
    "${target}"
    PRIVATE
      $<$<COMPILE_LANG_AND_ID:C,MSVC>:
        /W4
      >
      $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:
        /W4
      >
    )
  endif()
endfunction()
