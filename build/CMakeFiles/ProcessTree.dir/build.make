# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /root/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /root/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dawn/nju_os

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dawn/nju_os/build

# Include any dependencies generated for this target.
include CMakeFiles/ProcessTree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ProcessTree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ProcessTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProcessTree.dir/flags.make

CMakeFiles/ProcessTree.dir/pstree.cc.o: CMakeFiles/ProcessTree.dir/flags.make
CMakeFiles/ProcessTree.dir/pstree.cc.o: /home/dawn/nju_os/pstree.cc
CMakeFiles/ProcessTree.dir/pstree.cc.o: CMakeFiles/ProcessTree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dawn/nju_os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProcessTree.dir/pstree.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProcessTree.dir/pstree.cc.o -MF CMakeFiles/ProcessTree.dir/pstree.cc.o.d -o CMakeFiles/ProcessTree.dir/pstree.cc.o -c /home/dawn/nju_os/pstree.cc

CMakeFiles/ProcessTree.dir/pstree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProcessTree.dir/pstree.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dawn/nju_os/pstree.cc > CMakeFiles/ProcessTree.dir/pstree.cc.i

CMakeFiles/ProcessTree.dir/pstree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProcessTree.dir/pstree.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dawn/nju_os/pstree.cc -o CMakeFiles/ProcessTree.dir/pstree.cc.s

# Object files for target ProcessTree
ProcessTree_OBJECTS = \
"CMakeFiles/ProcessTree.dir/pstree.cc.o"

# External object files for target ProcessTree
ProcessTree_EXTERNAL_OBJECTS =

ProcessTree: CMakeFiles/ProcessTree.dir/pstree.cc.o
ProcessTree: CMakeFiles/ProcessTree.dir/build.make
ProcessTree: CMakeFiles/ProcessTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dawn/nju_os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProcessTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProcessTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProcessTree.dir/build: ProcessTree
.PHONY : CMakeFiles/ProcessTree.dir/build

CMakeFiles/ProcessTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProcessTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProcessTree.dir/clean

CMakeFiles/ProcessTree.dir/depend:
	cd /home/dawn/nju_os/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dawn/nju_os /home/dawn/nju_os /home/dawn/nju_os/build /home/dawn/nju_os/build /home/dawn/nju_os/build/CMakeFiles/ProcessTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProcessTree.dir/depend

