# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gemma/bullet3-2.87

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gemma/bullet-buid

# Include any dependencies generated for this target.
include test/gtest-1.7.0/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include test/gtest-1.7.0/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include test/gtest-1.7.0/CMakeFiles/gtest.dir/flags.make

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o: test/gtest-1.7.0/CMakeFiles/gtest.dir/flags.make
test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o: /home/gemma/bullet3-2.87/test/gtest-1.7.0/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o"
	cd /home/gemma/bullet-buid/test/gtest-1.7.0 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.o -c /home/gemma/bullet3-2.87/test/gtest-1.7.0/src/gtest-all.cc

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.i"
	cd /home/gemma/bullet-buid/test/gtest-1.7.0 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/test/gtest-1.7.0/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.i

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.s"
	cd /home/gemma/bullet-buid/test/gtest-1.7.0 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/test/gtest-1.7.0/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.s

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.requires:

.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.requires

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.provides: test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.requires
	$(MAKE) -f test/gtest-1.7.0/CMakeFiles/gtest.dir/build.make test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.provides.build
.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.provides

test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.provides.build: test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

test/gtest-1.7.0/libgtest.so: test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o
test/gtest-1.7.0/libgtest.so: test/gtest-1.7.0/CMakeFiles/gtest.dir/build.make
test/gtest-1.7.0/libgtest.so: test/gtest-1.7.0/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libgtest.so"
	cd /home/gemma/bullet-buid/test/gtest-1.7.0 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/gtest-1.7.0/CMakeFiles/gtest.dir/build: test/gtest-1.7.0/libgtest.so

.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/build

test/gtest-1.7.0/CMakeFiles/gtest.dir/requires: test/gtest-1.7.0/CMakeFiles/gtest.dir/src/gtest-all.o.requires

.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/requires

test/gtest-1.7.0/CMakeFiles/gtest.dir/clean:
	cd /home/gemma/bullet-buid/test/gtest-1.7.0 && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/clean

test/gtest-1.7.0/CMakeFiles/gtest.dir/depend:
	cd /home/gemma/bullet-buid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gemma/bullet3-2.87 /home/gemma/bullet3-2.87/test/gtest-1.7.0 /home/gemma/bullet-buid /home/gemma/bullet-buid/test/gtest-1.7.0 /home/gemma/bullet-buid/test/gtest-1.7.0/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/gtest-1.7.0/CMakeFiles/gtest.dir/depend

