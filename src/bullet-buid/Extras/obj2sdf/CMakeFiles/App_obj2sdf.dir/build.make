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
include Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/depend.make

# Include the progress variables for this target.
include Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/progress.make

# Include the compile flags for this target's objects.
include Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/flags.make

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/flags.make
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o: /home/gemma/bullet3-2.87/Extras/obj2sdf/obj2sdf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/App_obj2sdf.dir/obj2sdf.o -c /home/gemma/bullet3-2.87/Extras/obj2sdf/obj2sdf.cpp

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App_obj2sdf.dir/obj2sdf.i"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/Extras/obj2sdf/obj2sdf.cpp > CMakeFiles/App_obj2sdf.dir/obj2sdf.i

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App_obj2sdf.dir/obj2sdf.s"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/Extras/obj2sdf/obj2sdf.cpp -o CMakeFiles/App_obj2sdf.dir/obj2sdf.s

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.requires:

.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.requires

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.provides: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.requires
	$(MAKE) -f Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build.make Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.provides.build
.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.provides

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.provides.build: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o


Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/flags.make
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o: /home/gemma/bullet3-2.87/examples/Utils/b3ResourcePath.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o -c /home/gemma/bullet3-2.87/examples/Utils/b3ResourcePath.cpp

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.i"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/examples/Utils/b3ResourcePath.cpp > CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.i

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.s"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/examples/Utils/b3ResourcePath.cpp -o CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.s

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.requires:

.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.requires

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.provides: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.requires
	$(MAKE) -f Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build.make Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.provides.build
.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.provides

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.provides.build: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o


Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/flags.make
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o: /home/gemma/bullet3-2.87/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o -c /home/gemma/bullet3-2.87/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.i"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gemma/bullet3-2.87/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp > CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.i

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.s"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gemma/bullet3-2.87/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp -o CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.s

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.requires:

.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.requires

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.provides: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.requires
	$(MAKE) -f Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build.make Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.provides.build
.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.provides

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.provides.build: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o


# Object files for target App_obj2sdf
App_obj2sdf_OBJECTS = \
"CMakeFiles/App_obj2sdf.dir/obj2sdf.o" \
"CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o" \
"CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o"

# External object files for target App_obj2sdf
App_obj2sdf_EXTERNAL_OBJECTS =

Extras/obj2sdf/App_obj2sdf: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o
Extras/obj2sdf/App_obj2sdf: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o
Extras/obj2sdf/App_obj2sdf: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o
Extras/obj2sdf/App_obj2sdf: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build.make
Extras/obj2sdf/App_obj2sdf: src/Bullet3Common/libBullet3Common.so.2.87
Extras/obj2sdf/App_obj2sdf: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gemma/bullet-buid/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable App_obj2sdf"
	cd /home/gemma/bullet-buid/Extras/obj2sdf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/App_obj2sdf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build: Extras/obj2sdf/App_obj2sdf

.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/build

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/requires: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/obj2sdf.o.requires
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/requires: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/Utils/b3ResourcePath.o.requires
Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/requires: Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/__/__/examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.o.requires

.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/requires

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/clean:
	cd /home/gemma/bullet-buid/Extras/obj2sdf && $(CMAKE_COMMAND) -P CMakeFiles/App_obj2sdf.dir/cmake_clean.cmake
.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/clean

Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/depend:
	cd /home/gemma/bullet-buid && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gemma/bullet3-2.87 /home/gemma/bullet3-2.87/Extras/obj2sdf /home/gemma/bullet-buid /home/gemma/bullet-buid/Extras/obj2sdf /home/gemma/bullet-buid/Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Extras/obj2sdf/CMakeFiles/App_obj2sdf.dir/depend

