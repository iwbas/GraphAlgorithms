# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\GitHub\GraphAlgorithms\LR5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\GitHub\GraphAlgorithms\LR5\build

# Include any dependencies generated for this target.
include CMakeFiles/LR5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LR5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR5.dir/flags.make

CMakeFiles/LR5.dir/main.cpp.obj: CMakeFiles/LR5.dir/flags.make
CMakeFiles/LR5.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\GitHub\GraphAlgorithms\LR5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LR5.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LR5.dir\main.cpp.obj -c E:\GitHub\GraphAlgorithms\LR5\main.cpp

CMakeFiles/LR5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LR5.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\GitHub\GraphAlgorithms\LR5\main.cpp > CMakeFiles\LR5.dir\main.cpp.i

CMakeFiles/LR5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LR5.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\GitHub\GraphAlgorithms\LR5\main.cpp -o CMakeFiles\LR5.dir\main.cpp.s

# Object files for target LR5
LR5_OBJECTS = \
"CMakeFiles/LR5.dir/main.cpp.obj"

# External object files for target LR5
LR5_EXTERNAL_OBJECTS =

LR5.exe: CMakeFiles/LR5.dir/main.cpp.obj
LR5.exe: CMakeFiles/LR5.dir/build.make
LR5.exe: CMakeFiles/LR5.dir/linklibs.rsp
LR5.exe: CMakeFiles/LR5.dir/objects1.rsp
LR5.exe: CMakeFiles/LR5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\GitHub\GraphAlgorithms\LR5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LR5.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR5.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR5.dir/build: LR5.exe

.PHONY : CMakeFiles/LR5.dir/build

CMakeFiles/LR5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR5.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR5.dir/clean

CMakeFiles/LR5.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\GitHub\GraphAlgorithms\LR5 E:\GitHub\GraphAlgorithms\LR5 E:\GitHub\GraphAlgorithms\LR5\build E:\GitHub\GraphAlgorithms\LR5\build E:\GitHub\GraphAlgorithms\LR5\build\CMakeFiles\LR5.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LR5.dir/depend

