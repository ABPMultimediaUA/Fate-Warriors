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
include Extras/HACD/CMakeFiles/HACD.dir/depend.make

# Include the progress variables for this target.
include Extras/HACD/CMakeFiles/HACD.dir/progress.make

# Include the compile flags for this target's objects.
include Extras/HACD/CMakeFiles/HACD.dir/flags.make

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o: /home/gemma/bullet3-2.87/Extras/HACD/hacdGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdGraph.o -c /home/gemma/bullet3-2.87/Extras/HACD/hacdGraph.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdGraph.i"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/Extras/HACD/hacdGraph.cpp > CMakeFiles/HACD.dir/hacdGraph.i

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdGraph.s"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/Extras/HACD/hacdGraph.cpp -o CMakeFiles/HACD.dir/hacdGraph.s

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.requires:

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.requires

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.provides: Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.requires
	$(MAKE) -f Extras/HACD/CMakeFiles/HACD.dir/build.make Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.provides.build
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.provides

Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.provides.build: Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o


Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o: /home/gemma/bullet3-2.87/Extras/HACD/hacdHACD.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdHACD.o -c /home/gemma/bullet3-2.87/Extras/HACD/hacdHACD.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdHACD.i"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/Extras/HACD/hacdHACD.cpp > CMakeFiles/HACD.dir/hacdHACD.i

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdHACD.s"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/Extras/HACD/hacdHACD.cpp -o CMakeFiles/HACD.dir/hacdHACD.s

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.requires:

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.requires

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.provides: Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.requires
	$(MAKE) -f Extras/HACD/CMakeFiles/HACD.dir/build.make Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.provides.build
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.provides

Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.provides.build: Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o


Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o: /home/gemma/bullet3-2.87/Extras/HACD/hacdICHull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdICHull.o -c /home/gemma/bullet3-2.87/Extras/HACD/hacdICHull.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdICHull.i"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/Extras/HACD/hacdICHull.cpp > CMakeFiles/HACD.dir/hacdICHull.i

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdICHull.s"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/Extras/HACD/hacdICHull.cpp -o CMakeFiles/HACD.dir/hacdICHull.s

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.requires:

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.requires

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.provides: Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.requires
	$(MAKE) -f Extras/HACD/CMakeFiles/HACD.dir/build.make Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.provides.build
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.provides

Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.provides.build: Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o


Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o: Extras/HACD/CMakeFiles/HACD.dir/flags.make
Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o: /home/gemma/bullet3-2.87/Extras/HACD/hacdManifoldMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HACD.dir/hacdManifoldMesh.o -c /home/gemma/bullet3-2.87/Extras/HACD/hacdManifoldMesh.cpp

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HACD.dir/hacdManifoldMesh.i"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/Extras/HACD/hacdManifoldMesh.cpp > CMakeFiles/HACD.dir/hacdManifoldMesh.i

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HACD.dir/hacdManifoldMesh.s"
	cd /home/gemma/bullet-buid/Extras/HACD && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/Extras/HACD/hacdManifoldMesh.cpp -o CMakeFiles/HACD.dir/hacdManifoldMesh.s

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.requires:

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.requires

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.provides: Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.requires
	$(MAKE) -f Extras/HACD/CMakeFiles/HACD.dir/build.make Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.provides.build
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.provides

Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.provides.build: Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o


# Object files for target HACD
HACD_OBJECTS = \
"CMakeFiles/HACD.dir/hacdGraph.o" \
"CMakeFiles/HACD.dir/hacdHACD.o" \
"CMakeFiles/HACD.dir/hacdICHull.o" \
"CMakeFiles/HACD.dir/hacdManifoldMesh.o"

# External object files for target HACD
HACD_EXTERNAL_OBJECTS =

Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o
Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o
Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o
Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o
Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/build.make
Extras/HACD/libHACD.so.2.87: Extras/HACD/CMakeFiles/HACD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libHACD.so"
	cd /home/gemma/bullet-buid/Extras/HACD && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HACD.dir/link.txt --verbose=$(VERBOSE)
	cd /home/gemma/bullet-buid/Extras/HACD && $(CMAKE_COMMAND) -E cmake_symlink_library libHACD.so.2.87 libHACD.so.2.87 libHACD.so

Extras/HACD/libHACD.so: Extras/HACD/libHACD.so.2.87
	@$(CMAKE_COMMAND) -E touch_nocreate Extras/HACD/libHACD.so

# Rule to build all files generated by this target.
Extras/HACD/CMakeFiles/HACD.dir/build: Extras/HACD/libHACD.so

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/build

Extras/HACD/CMakeFiles/HACD.dir/requires: Extras/HACD/CMakeFiles/HACD.dir/hacdGraph.o.requires
Extras/HACD/CMakeFiles/HACD.dir/requires: Extras/HACD/CMakeFiles/HACD.dir/hacdHACD.o.requires
Extras/HACD/CMakeFiles/HACD.dir/requires: Extras/HACD/CMakeFiles/HACD.dir/hacdICHull.o.requires
Extras/HACD/CMakeFiles/HACD.dir/requires: Extras/HACD/CMakeFiles/HACD.dir/hacdManifoldMesh.o.requires

.PHONY : Extras/HACD/CMakeFiles/HACD.dir/requires

Extras/HACD/CMakeFiles/HACD.dir/clean:
	cd /home/gemma/bullet-buid/Extras/HACD && $(CMAKE_COMMAND) -P CMakeFiles/HACD.dir/cmake_clean.cmake
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/clean

Extras/HACD/CMakeFiles/HACD.dir/depend:
	cd /home/gemma/bullet-buid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gemma/bullet3-2.87 /home/gemma/bullet3-2.87/Extras/HACD /home/gemma/bullet-buid /home/gemma/bullet-buid/Extras/HACD /home/gemma/bullet-buid/Extras/HACD/CMakeFiles/HACD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Extras/HACD/CMakeFiles/HACD.dir/depend

