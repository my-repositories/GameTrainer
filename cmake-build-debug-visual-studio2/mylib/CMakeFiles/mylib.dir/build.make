# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\soft\CLion2019.3.4\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\soft\CLion2019.3.4\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\projects\my-repositories\GameTrainer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

# Include any dependencies generated for this target.
include mylib\CMakeFiles\mylib.dir\depend.make

# Include the progress variables for this target.
include mylib\CMakeFiles\mylib.dir\progress.make

# Include the compile flags for this target's objects.
include mylib\CMakeFiles\mylib.dir\flags.make

mylib\CMakeFiles\mylib.dir\src\config.cpp.obj: mylib\CMakeFiles\mylib.dir\flags.make
mylib\CMakeFiles\mylib.dir\src\config.cpp.obj: ..\mylib\src\config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mylib/CMakeFiles/mylib.dir/src/config.cpp.obj"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\mylib.dir\src\config.cpp.obj /FdCMakeFiles\mylib.dir\mylib.pdb /FS -c D:\projects\my-repositories\GameTrainer\mylib\src\config.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/config.cpp.i"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe > CMakeFiles\mylib.dir\src\config.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\projects\my-repositories\GameTrainer\mylib\src\config.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/config.cpp.s"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\mylib.dir\src\config.cpp.s /c D:\projects\my-repositories\GameTrainer\mylib\src\config.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\gg.cpp.obj: mylib\CMakeFiles\mylib.dir\flags.make
mylib\CMakeFiles\mylib.dir\src\gg.cpp.obj: ..\mylib\src\gg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object mylib/CMakeFiles/mylib.dir/src/gg.cpp.obj"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\mylib.dir\src\gg.cpp.obj /FdCMakeFiles\mylib.dir\mylib.pdb /FS -c D:\projects\my-repositories\GameTrainer\mylib\src\gg.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\gg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/gg.cpp.i"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe > CMakeFiles\mylib.dir\src\gg.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\projects\my-repositories\GameTrainer\mylib\src\gg.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\gg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/gg.cpp.s"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\mylib.dir\src\gg.cpp.s /c D:\projects\my-repositories\GameTrainer\mylib\src\gg.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\lua-wrapper.cpp.obj: mylib\CMakeFiles\mylib.dir\flags.make
mylib\CMakeFiles\mylib.dir\src\lua-wrapper.cpp.obj: ..\mylib\src\lua-wrapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object mylib/CMakeFiles/mylib.dir/src/lua-wrapper.cpp.obj"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\mylib.dir\src\lua-wrapper.cpp.obj /FdCMakeFiles\mylib.dir\mylib.pdb /FS -c D:\projects\my-repositories\GameTrainer\mylib\src\lua-wrapper.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\lua-wrapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/src/lua-wrapper.cpp.i"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe > CMakeFiles\mylib.dir\src\lua-wrapper.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\projects\my-repositories\GameTrainer\mylib\src\lua-wrapper.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

mylib\CMakeFiles\mylib.dir\src\lua-wrapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/src/lua-wrapper.cpp.s"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\mylib.dir\src\lua-wrapper.cpp.s /c D:\projects\my-repositories\GameTrainer\mylib\src\lua-wrapper.cpp
<<
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

# Object files for target mylib
mylib_OBJECTS = \
"CMakeFiles\mylib.dir\src\config.cpp.obj" \
"CMakeFiles\mylib.dir\src\gg.cpp.obj" \
"CMakeFiles\mylib.dir\src\lua-wrapper.cpp.obj"

# External object files for target mylib
mylib_EXTERNAL_OBJECTS =

..\app\deps\lib\mylib.lib: mylib\CMakeFiles\mylib.dir\src\config.cpp.obj
..\app\deps\lib\mylib.lib: mylib\CMakeFiles\mylib.dir\src\gg.cpp.obj
..\app\deps\lib\mylib.lib: mylib\CMakeFiles\mylib.dir\src\lua-wrapper.cpp.obj
..\app\deps\lib\mylib.lib: mylib\CMakeFiles\mylib.dir\build.make
..\app\deps\lib\mylib.lib: mylib\CMakeFiles\mylib.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ..\..\app\deps\lib\mylib.lib"
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	$(CMAKE_COMMAND) -P CMakeFiles\mylib.dir\cmake_clean_target.cmake
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	C:\soft\vs2019\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86\link.exe /lib /nologo /machine:X86 /out:..\..\app\deps\lib\mylib.lib @CMakeFiles\mylib.dir\objects1.rsp 
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2

# Rule to build all files generated by this target.
mylib\CMakeFiles\mylib.dir\build: ..\app\deps\lib\mylib.lib

.PHONY : mylib\CMakeFiles\mylib.dir\build

mylib\CMakeFiles\mylib.dir\clean:
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib
	$(CMAKE_COMMAND) -P CMakeFiles\mylib.dir\cmake_clean.cmake
	cd D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2
.PHONY : mylib\CMakeFiles\mylib.dir\clean

mylib\CMakeFiles\mylib.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\projects\my-repositories\GameTrainer D:\projects\my-repositories\GameTrainer\mylib D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2 D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib D:\projects\my-repositories\GameTrainer\cmake-build-debug-visual-studio2\mylib\CMakeFiles\mylib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : mylib\CMakeFiles\mylib.dir\depend

