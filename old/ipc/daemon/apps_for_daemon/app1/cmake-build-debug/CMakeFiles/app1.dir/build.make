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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/app1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/app1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app1.dir/flags.make

CMakeFiles/app1.dir/app1.cpp.o: CMakeFiles/app1.dir/flags.make
CMakeFiles/app1.dir/app1.cpp.o: ../app1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/app1.dir/app1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app1.dir/app1.cpp.o -c "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/app1.cpp"

CMakeFiles/app1.dir/app1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app1.dir/app1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/app1.cpp" > CMakeFiles/app1.dir/app1.cpp.i

CMakeFiles/app1.dir/app1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app1.dir/app1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/app1.cpp" -o CMakeFiles/app1.dir/app1.cpp.s

# Object files for target app1
app1_OBJECTS = \
"CMakeFiles/app1.dir/app1.cpp.o"

# External object files for target app1
app1_EXTERNAL_OBJECTS =

app1: CMakeFiles/app1.dir/app1.cpp.o
app1: CMakeFiles/app1.dir/build.make
app1: CMakeFiles/app1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable app1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app1.dir/build: app1

.PHONY : CMakeFiles/app1.dir/build

CMakeFiles/app1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app1.dir/clean

CMakeFiles/app1.dir/depend:
	cd "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1" "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1" "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/apps_for_daemon/app1/cmake-build-debug/CMakeFiles/app1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/app1.dir/depend

