# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hitesh/CLionProjects/cz4031-database-system-principles

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/memory-pool.h.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/memory-pool.h.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memory-pool.h.dir/flags.make

CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o: CMakeFiles/memory-pool.h.dir/flags.make
CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o: ../memory-pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o -c /home/hitesh/CLionProjects/cz4031-database-system-principles/memory-pool.cpp

CMakeFiles/memory-pool.h.dir/memory-pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memory-pool.h.dir/memory-pool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hitesh/CLionProjects/cz4031-database-system-principles/memory-pool.cpp > CMakeFiles/memory-pool.h.dir/memory-pool.cpp.i

CMakeFiles/memory-pool.h.dir/memory-pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memory-pool.h.dir/memory-pool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hitesh/CLionProjects/cz4031-database-system-principles/memory-pool.cpp -o CMakeFiles/memory-pool.h.dir/memory-pool.cpp.s

CMakeFiles/memory-pool.h.dir/main.cpp.o: CMakeFiles/memory-pool.h.dir/flags.make
CMakeFiles/memory-pool.h.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/memory-pool.h.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memory-pool.h.dir/main.cpp.o -c /home/hitesh/CLionProjects/cz4031-database-system-principles/main.cpp

CMakeFiles/memory-pool.h.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memory-pool.h.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hitesh/CLionProjects/cz4031-database-system-principles/main.cpp > CMakeFiles/memory-pool.h.dir/main.cpp.i

CMakeFiles/memory-pool.h.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memory-pool.h.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hitesh/CLionProjects/cz4031-database-system-principles/main.cpp -o CMakeFiles/memory-pool.h.dir/main.cpp.s

CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o: CMakeFiles/memory-pool.h.dir/flags.make
CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o: ../b-plus-tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o -c /home/hitesh/CLionProjects/cz4031-database-system-principles/b-plus-tree.cpp

CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hitesh/CLionProjects/cz4031-database-system-principles/b-plus-tree.cpp > CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.i

CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hitesh/CLionProjects/cz4031-database-system-principles/b-plus-tree.cpp -o CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.s

# Object files for target memory-pool.h
memory__pool_h_OBJECTS = \
"CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o" \
"CMakeFiles/memory-pool.h.dir/main.cpp.o" \
"CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o"

# External object files for target memory-pool.h
memory__pool_h_EXTERNAL_OBJECTS =

memory-pool.h: CMakeFiles/memory-pool.h.dir/memory-pool.cpp.o
memory-pool.h: CMakeFiles/memory-pool.h.dir/main.cpp.o
memory-pool.h: CMakeFiles/memory-pool.h.dir/b-plus-tree.cpp.o
memory-pool.h: CMakeFiles/memory-pool.h.dir/build.make
memory-pool.h: CMakeFiles/memory-pool.h.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable memory-pool.h"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memory-pool.h.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memory-pool.h.dir/build: memory-pool.h

.PHONY : CMakeFiles/memory-pool.h.dir/build

CMakeFiles/memory-pool.h.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memory-pool.h.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memory-pool.h.dir/clean

CMakeFiles/memory-pool.h.dir/depend:
	cd /home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hitesh/CLionProjects/cz4031-database-system-principles /home/hitesh/CLionProjects/cz4031-database-system-principles /home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug /home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug /home/hitesh/CLionProjects/cz4031-database-system-principles/cmake-build-debug/CMakeFiles/memory-pool.h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/memory-pool.h.dir/depend

