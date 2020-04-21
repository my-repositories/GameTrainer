@echo off

:loop

if "%1" == "" goto :finalize
if /i "%1" == "x86" goto :x86
if /i "%1" == "x64" goto :x64
if /i "%1" == "msvc15" goto :msvc15
if /i "%1" == "msvc16" goto :msvc16

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Version

:version
set GT_VERSION=%1
shift

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Configuration

:configuration
set GT_CONFIGURATION=%1
shift
goto :loop

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Platform

:x86
set TARGET_CPU=Win32
set CMAKE_GENERATOR_SUFFIX=
set GT_PLATFORM=x86
shift
goto :loop

:x64
set TARGET_CPU=x64
set CMAKE_GENERATOR_SUFFIX= Win64
set GT_PLATFORM=x64
shift
goto :loop

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Toolchain

:msvc15
set TOOLCHAIN=msvc15
set CMAKE_GENERATOR=Visual Studio 15 2017
shift
goto :loop

:msvc16
set TOOLCHAIN=msvc16
set CMAKE_GENERATOR=Visual Studio 16 2019
set CMAKE_GENERATOR_SUFFIX=
set CMAKE_GENERATOR_ARCH= -A %TARGET_CPU%
shift
goto :loop

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:finalize

if "%TOOLCHAIN%" == "" goto :msvc15
if "%TARGET_CPU%" == "" goto :x64
if "%PROJECT_NAME%" == "" set PROJECT_NAME=GameTrainer
if "%GT_CONFIGURATION%" == "" set GT_CONFIGURATION=Release
if "%GT_VERSION%" == "" set GT_VERSION=master

set CMAKE_CONFIGURE_FLAGS= ^
	-B build ^
	-S . ^
	-G "%CMAKE_GENERATOR%%CMAKE_GENERATOR_SUFFIX%"%CMAKE_GENERATOR_ARCH% ^
	-DGT_CONFIGURATION=%GT_CONFIGURATION% ^
	-DGT_PLATFORM=%GT_PLATFORM% ^
	-DGT_OS=win ^
	-DGT_PROJECT_NAME=%PROJECT_NAME% ^
	-DGT_PROJECT_VERSION=%GT_VERSION% ^
	-DGT_TOOLCHAIN=%TOOLCHAIN% ^
	.

set CMAKE_BUILD_FLAGS= ^
    --build build ^
	--config %GT_CONFIGURATION% ^
	-- ^
	/nologo ^
	/verbosity:minimal ^
	/consoleloggerparameters:Summary
