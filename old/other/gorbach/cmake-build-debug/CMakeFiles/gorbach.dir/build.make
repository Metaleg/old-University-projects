# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/gorbach.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gorbach.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gorbach.dir/flags.make

CMakeFiles/gorbach.dir/main.cpp.o: CMakeFiles/gorbach.dir/flags.make
CMakeFiles/gorbach.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gorbach.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gorbach.dir/main.cpp.o -c "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/main.cpp"

CMakeFiles/gorbach.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gorbach.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/main.cpp" > CMakeFiles/gorbach.dir/main.cpp.i

CMakeFiles/gorbach.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gorbach.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/main.cpp" -o CMakeFiles/gorbach.dir/main.cpp.s

# Object files for target gorbach
gorbach_OBJECTS = \
"CMakeFiles/gorbach.dir/main.cpp.o"

# External object files for target gorbach
gorbach_EXTERNAL_OBJECTS =

gorbach: CMakeFiles/gorbach.dir/main.cpp.o
gorbach: CMakeFiles/gorbach.dir/build.make
gorbach: CMakeFiles/gorbach.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gorbach"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gorbach.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gorbach.dir/build: gorbach

.PHONY : CMakeFiles/gorbach.dir/build

CMakeFiles/gorbach.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gorbach.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gorbach.dir/clean

CMakeFiles/gorbach.dir/depend:
	cd "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach" "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach" "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/gorbach/cmake-build-debug/CMakeFiles/gorbach.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gorbach.dir/depend
