@echo off

set TARGET=pl0_compiler.exe

set SRC_DIR=..\src\
set SRC_FILES=%SRC_DIR%\main.c

set BUILD_DIR=build

set CL_FLAGS=/GA /FC /Gd /std:c17 /Zi /MD /nologo /utf-8 /W4 /WX

set LIBS=
set LINK_FLAGS=/out:%TARGET% /MACHINE:x64 /nologo %LIBS%

pushd %BUILD_DIR%

cl %CL_FLAGS% %SRC_FILES% /link %LINK_FLAGS%

IF /I "%1"=="run" (.\%TARGET%)

popd