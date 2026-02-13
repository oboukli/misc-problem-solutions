REM  Copyright (c) Omar Boukli-Hacene. All rights reserved.
REM  Distributed under an MIT-style license that can be
REM  found in the LICENSE file.

REM  SPDX-License-Identifier: MIT

@echo off

for /f "usebackq tokens=*" %%i in (`
  "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" ^
  -latest ^
  -products * ^
  -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 ^
  -property installationPath
`) do (
  call "%%i\VC\Auxiliary\Build\vcvars64.bat"
)
