# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/linux_daemon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linux_daemon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linux_daemon.dir/flags.make

CMakeFiles/linux_daemon.dir/daemon.c.o: CMakeFiles/linux_daemon.dir/flags.make
CMakeFiles/linux_daemon.dir/daemon.c.o: ../daemon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/linux_daemon.dir/daemon.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/linux_daemon.dir/daemon.c.o   -c "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/daemon.c"

CMakeFiles/linux_daemon.dir/daemon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linux_daemon.dir/daemon.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/daemon.c" > CMakeFiles/linux_daemon.dir/daemon.c.i

CMakeFiles/linux_daemon.dir/daemon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linux_daemon.dir/daemon.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/daemon.c" -o CMakeFiles/linux_daemon.dir/daemon.c.s

CMakeFiles/linux_daemon.dir/work_with_config.c.o: CMakeFiles/linux_daemon.dir/flags.make
CMakeFiles/linux_daemon.dir/work_with_config.c.o: ../work_with_config.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/linux_daemon.dir/work_with_config.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/linux_daemon.dir/work_with_config.c.o   -c "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/work_with_config.c"

CMakeFiles/linux_daemon.dir/work_with_config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linux_daemon.dir/work_with_config.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/work_with_config.c" > CMakeFiles/linux_daemon.dir/work_with_config.c.i

CMakeFiles/linux_daemon.dir/work_with_config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linux_daemon.dir/work_with_config.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/work_with_config.c" -o CMakeFiles/linux_daemon.dir/work_with_config.c.s

# Object files for target linux_daemon
linux_daemon_OBJECTS = \
"CMakeFiles/linux_daemon.dir/daemon.c.o" \
"CMakeFiles/linux_daemon.dir/work_with_config.c.o"

# External object files for target linux_daemon
linux_daemon_EXTERNAL_OBJECTS =

linux_daemon: CMakeFiles/linux_daemon.dir/daemon.c.o
linux_daemon: CMakeFiles/linux_daemon.dir/work_with_config.c.o
linux_daemon: CMakeFiles/linux_daemon.dir/build.make
linux_daemon: CMakeFiles/linux_daemon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable linux_daemon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linux_daemon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linux_daemon.dir/build: linux_daemon

.PHONY : CMakeFiles/linux_daemon.dir/build

CMakeFiles/linux_daemon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linux_daemon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linux_daemon.dir/clean

CMakeFiles/linux_daemon.dir/depend:
	cd "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon" "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon" "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug" "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug" "/media/vitakadabr/Local disk/Documents/CLionProjects/linux_daemon/cmake-build-debug/CMakeFiles/linux_daemon.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/linux_daemon.dir/depend

