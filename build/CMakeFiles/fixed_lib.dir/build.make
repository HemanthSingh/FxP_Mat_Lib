# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/He-Man/Desktop/Fixed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/He-Man/Desktop/Fixed/build

# Include any dependencies generated for this target.
include CMakeFiles/fixed_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fixed_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fixed_lib.dir/flags.make

CMakeFiles/fixed_lib.dir/src/test.c.o: CMakeFiles/fixed_lib.dir/flags.make
CMakeFiles/fixed_lib.dir/src/test.c.o: ../src/test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/He-Man/Desktop/Fixed/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fixed_lib.dir/src/test.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fixed_lib.dir/src/test.c.o   -c /Users/He-Man/Desktop/Fixed/src/test.c

CMakeFiles/fixed_lib.dir/src/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fixed_lib.dir/src/test.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/He-Man/Desktop/Fixed/src/test.c > CMakeFiles/fixed_lib.dir/src/test.c.i

CMakeFiles/fixed_lib.dir/src/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fixed_lib.dir/src/test.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/He-Man/Desktop/Fixed/src/test.c -o CMakeFiles/fixed_lib.dir/src/test.c.s

# Object files for target fixed_lib
fixed_lib_OBJECTS = \
"CMakeFiles/fixed_lib.dir/src/test.c.o"

# External object files for target fixed_lib
fixed_lib_EXTERNAL_OBJECTS =

fixed_lib: CMakeFiles/fixed_lib.dir/src/test.c.o
fixed_lib: CMakeFiles/fixed_lib.dir/build.make
fixed_lib: libcordic/liblibcordic.a
fixed_lib: libarm/liblibarm.a
fixed_lib: CMakeFiles/fixed_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/He-Man/Desktop/Fixed/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fixed_lib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fixed_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fixed_lib.dir/build: fixed_lib

.PHONY : CMakeFiles/fixed_lib.dir/build

CMakeFiles/fixed_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fixed_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fixed_lib.dir/clean

CMakeFiles/fixed_lib.dir/depend:
	cd /Users/He-Man/Desktop/Fixed/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/He-Man/Desktop/Fixed /Users/He-Man/Desktop/Fixed /Users/He-Man/Desktop/Fixed/build /Users/He-Man/Desktop/Fixed/build /Users/He-Man/Desktop/Fixed/build/CMakeFiles/fixed_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fixed_lib.dir/depend
