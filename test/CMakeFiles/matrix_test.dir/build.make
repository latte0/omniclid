# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.5.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.5.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/k/dev/cpp/omniclid/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/k/dev/cpp/omniclid/test

# Include any dependencies generated for this target.
include CMakeFiles/matrix_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matrix_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrix_test.dir/flags.make

CMakeFiles/matrix_test.dir/matrix_test.cpp.o: CMakeFiles/matrix_test.dir/flags.make
CMakeFiles/matrix_test.dir/matrix_test.cpp.o: matrix_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/k/dev/cpp/omniclid/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matrix_test.dir/matrix_test.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matrix_test.dir/matrix_test.cpp.o -c /Users/k/dev/cpp/omniclid/test/matrix_test.cpp

CMakeFiles/matrix_test.dir/matrix_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrix_test.dir/matrix_test.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/k/dev/cpp/omniclid/test/matrix_test.cpp > CMakeFiles/matrix_test.dir/matrix_test.cpp.i

CMakeFiles/matrix_test.dir/matrix_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrix_test.dir/matrix_test.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/k/dev/cpp/omniclid/test/matrix_test.cpp -o CMakeFiles/matrix_test.dir/matrix_test.cpp.s

CMakeFiles/matrix_test.dir/matrix_test.cpp.o.requires:

.PHONY : CMakeFiles/matrix_test.dir/matrix_test.cpp.o.requires

CMakeFiles/matrix_test.dir/matrix_test.cpp.o.provides: CMakeFiles/matrix_test.dir/matrix_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/matrix_test.dir/build.make CMakeFiles/matrix_test.dir/matrix_test.cpp.o.provides.build
.PHONY : CMakeFiles/matrix_test.dir/matrix_test.cpp.o.provides

CMakeFiles/matrix_test.dir/matrix_test.cpp.o.provides.build: CMakeFiles/matrix_test.dir/matrix_test.cpp.o


# Object files for target matrix_test
matrix_test_OBJECTS = \
"CMakeFiles/matrix_test.dir/matrix_test.cpp.o"

# External object files for target matrix_test
matrix_test_EXTERNAL_OBJECTS =

matrix_test: CMakeFiles/matrix_test.dir/matrix_test.cpp.o
matrix_test: CMakeFiles/matrix_test.dir/build.make
matrix_test: /usr/local/lib/libgtest.a
matrix_test: /usr/local/lib/libgtest_main.a
matrix_test: CMakeFiles/matrix_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/k/dev/cpp/omniclid/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matrix_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrix_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrix_test.dir/build: matrix_test

.PHONY : CMakeFiles/matrix_test.dir/build

CMakeFiles/matrix_test.dir/requires: CMakeFiles/matrix_test.dir/matrix_test.cpp.o.requires

.PHONY : CMakeFiles/matrix_test.dir/requires

CMakeFiles/matrix_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrix_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrix_test.dir/clean

CMakeFiles/matrix_test.dir/depend:
	cd /Users/k/dev/cpp/omniclid/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/k/dev/cpp/omniclid/test /Users/k/dev/cpp/omniclid/test /Users/k/dev/cpp/omniclid/test /Users/k/dev/cpp/omniclid/test /Users/k/dev/cpp/omniclid/test/CMakeFiles/matrix_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrix_test.dir/depend
