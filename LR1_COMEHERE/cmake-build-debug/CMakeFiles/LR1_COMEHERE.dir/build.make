# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LR1_COMEHERE.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LR1_COMEHERE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR1_COMEHERE.dir/flags.make

CMakeFiles/LR1_COMEHERE.dir/main.cpp.obj: CMakeFiles/LR1_COMEHERE.dir/flags.make
CMakeFiles/LR1_COMEHERE.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LR1_COMEHERE.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LR1_COMEHERE.dir\main.cpp.obj -c D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\main.cpp

CMakeFiles/LR1_COMEHERE.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LR1_COMEHERE.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\main.cpp > CMakeFiles\LR1_COMEHERE.dir\main.cpp.i

CMakeFiles/LR1_COMEHERE.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LR1_COMEHERE.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\main.cpp -o CMakeFiles\LR1_COMEHERE.dir\main.cpp.s

# Object files for target LR1_COMEHERE
LR1_COMEHERE_OBJECTS = \
"CMakeFiles/LR1_COMEHERE.dir/main.cpp.obj"

# External object files for target LR1_COMEHERE
LR1_COMEHERE_EXTERNAL_OBJECTS =

LR1_COMEHERE.exe: CMakeFiles/LR1_COMEHERE.dir/main.cpp.obj
LR1_COMEHERE.exe: CMakeFiles/LR1_COMEHERE.dir/build.make
LR1_COMEHERE.exe: CMakeFiles/LR1_COMEHERE.dir/linklibs.rsp
LR1_COMEHERE.exe: CMakeFiles/LR1_COMEHERE.dir/objects1.rsp
LR1_COMEHERE.exe: CMakeFiles/LR1_COMEHERE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LR1_COMEHERE.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR1_COMEHERE.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR1_COMEHERE.dir/build: LR1_COMEHERE.exe

.PHONY : CMakeFiles/LR1_COMEHERE.dir/build

CMakeFiles/LR1_COMEHERE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR1_COMEHERE.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR1_COMEHERE.dir/clean

CMakeFiles/LR1_COMEHERE.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug D:\GitHub\GraphAlgorithmsLR1\LR1_COMEHERE\cmake-build-debug\CMakeFiles\LR1_COMEHERE.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LR1_COMEHERE.dir/depend

