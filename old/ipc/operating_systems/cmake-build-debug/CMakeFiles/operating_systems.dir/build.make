# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/metalleg/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.5281.33/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/metalleg/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.5281.33/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/metalleg/CLionProjects/operating_systems

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/metalleg/CLionProjects/operating_systems/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/operating_systems.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/operating_systems.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/operating_systems.dir/flags.make

CMakeFiles/operating_systems.dir/main.c.o: CMakeFiles/operating_systems.dir/flags.make
CMakeFiles/operating_systems.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/metalleg/CLionProjects/operating_systems/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/operating_systems.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/operating_systems.dir/main.c.o   -c /home/metalleg/CLionProjects/operating_systems/main.c

CMakeFiles/operating_systems.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/operating_systems.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/metalleg/CLionProjects/operating_systems/main.c > CMakeFiles/operating_systems.dir/main.c.i

CMakeFiles/operating_systems.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/operating_systems.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/metalleg/CLionProjects/operating_systems/main.c -o CMakeFiles/operating_systems.dir/main.c.s

CMakeFiles/operating_systems.dir/main.c.o.requires:

.PHONY : CMakeFiles/operating_systems.dir/main.c.o.requires

CMakeFiles/operating_systems.dir/main.c.o.provides: CMakeFiles/operating_systems.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/operating_systems.dir/build.make CMakeFiles/operating_systems.dir/main.c.o.provides.build
.PHONY : CMakeFiles/operating_systems.dir/main.c.o.provides

CMakeFiles/operating_systems.dir/main.c.o.provides.build: CMakeFiles/operating_systems.dir/main.c.o


# Object files for target operating_systems
operating_systems_OBJECTS = \
"CMakeFiles/operating_systems.dir/main.c.o"

# External object files for target operating_systems
operating_systems_EXTERNAL_OBJECTS =

operating_systems: CMakeFiles/operating_systems.dir/main.c.o
operating_systems: CMakeFiles/operating_systems.dir/build.make
operating_systems: CMakeFiles/operating_systems.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/metalleg/CLionProjects/operating_systems/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable operating_systems"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/operating_systems.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/operating_systems.dir/build: operating_systems

.PHONY : CMakeFiles/operating_systems.dir/build

CMakeFiles/operating_systems.dir/requires: CMakeFiles/operating_systems.dir/main.c.o.requires

.PHONY : CMakeFiles/operating_systems.dir/requires

CMakeFiles/operating_systems.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/operating_systems.dir/cmake_clean.cmake
.PHONY : CMakeFiles/operating_systems.dir/clean

CMakeFiles/operating_systems.dir/depend:
	cd /home/metalleg/CLionProjects/operating_systems/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/metalleg/CLionProjects/operating_systems /home/metalleg/CLionProjects/operating_systems /home/metalleg/CLionProjects/operating_systems/cmake-build-debug /home/metalleg/CLionProjects/operating_systems/cmake-build-debug /home/metalleg/CLionProjects/operating_systems/cmake-build-debug/CMakeFiles/operating_systems.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/operating_systems.dir/depend

