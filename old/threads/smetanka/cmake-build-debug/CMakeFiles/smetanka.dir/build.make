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
CMAKE_COMMAND = /home/metalleg/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4668.70/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/metalleg/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4668.70/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/metalleg/CLionProjects/smetanka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/metalleg/CLionProjects/smetanka/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/smetanka.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/smetanka.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smetanka.dir/flags.make

CMakeFiles/smetanka.dir/main.c.o: CMakeFiles/smetanka.dir/flags.make
CMakeFiles/smetanka.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/metalleg/CLionProjects/smetanka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/smetanka.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/smetanka.dir/main.c.o   -c /home/metalleg/CLionProjects/smetanka/main.c

CMakeFiles/smetanka.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/smetanka.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/metalleg/CLionProjects/smetanka/main.c > CMakeFiles/smetanka.dir/main.c.i

CMakeFiles/smetanka.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/smetanka.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/metalleg/CLionProjects/smetanka/main.c -o CMakeFiles/smetanka.dir/main.c.s

CMakeFiles/smetanka.dir/main.c.o.requires:

.PHONY : CMakeFiles/smetanka.dir/main.c.o.requires

CMakeFiles/smetanka.dir/main.c.o.provides: CMakeFiles/smetanka.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/smetanka.dir/build.make CMakeFiles/smetanka.dir/main.c.o.provides.build
.PHONY : CMakeFiles/smetanka.dir/main.c.o.provides

CMakeFiles/smetanka.dir/main.c.o.provides.build: CMakeFiles/smetanka.dir/main.c.o


# Object files for target smetanka
smetanka_OBJECTS = \
"CMakeFiles/smetanka.dir/main.c.o"

# External object files for target smetanka
smetanka_EXTERNAL_OBJECTS =

smetanka: CMakeFiles/smetanka.dir/main.c.o
smetanka: CMakeFiles/smetanka.dir/build.make
smetanka: CMakeFiles/smetanka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/metalleg/CLionProjects/smetanka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable smetanka"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smetanka.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smetanka.dir/build: smetanka

.PHONY : CMakeFiles/smetanka.dir/build

CMakeFiles/smetanka.dir/requires: CMakeFiles/smetanka.dir/main.c.o.requires

.PHONY : CMakeFiles/smetanka.dir/requires

CMakeFiles/smetanka.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smetanka.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smetanka.dir/clean

CMakeFiles/smetanka.dir/depend:
	cd /home/metalleg/CLionProjects/smetanka/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/metalleg/CLionProjects/smetanka /home/metalleg/CLionProjects/smetanka /home/metalleg/CLionProjects/smetanka/cmake-build-debug /home/metalleg/CLionProjects/smetanka/cmake-build-debug /home/metalleg/CLionProjects/smetanka/cmake-build-debug/CMakeFiles/smetanka.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smetanka.dir/depend

