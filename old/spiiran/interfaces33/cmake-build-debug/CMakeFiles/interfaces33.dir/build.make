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
CMAKE_SOURCE_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/interfaces33.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/interfaces33.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interfaces33.dir/flags.make

CMakeFiles/interfaces33.dir/imu.cpp.o: CMakeFiles/interfaces33.dir/flags.make
CMakeFiles/interfaces33.dir/imu.cpp.o: ../imu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/interfaces33.dir/imu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interfaces33.dir/imu.cpp.o -c "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/imu.cpp"

CMakeFiles/interfaces33.dir/imu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interfaces33.dir/imu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/imu.cpp" > CMakeFiles/interfaces33.dir/imu.cpp.i

CMakeFiles/interfaces33.dir/imu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interfaces33.dir/imu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/imu.cpp" -o CMakeFiles/interfaces33.dir/imu.cpp.s

CMakeFiles/interfaces33.dir/main.cpp.o: CMakeFiles/interfaces33.dir/flags.make
CMakeFiles/interfaces33.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/interfaces33.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interfaces33.dir/main.cpp.o -c "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/main.cpp"

CMakeFiles/interfaces33.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interfaces33.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/main.cpp" > CMakeFiles/interfaces33.dir/main.cpp.i

CMakeFiles/interfaces33.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interfaces33.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/main.cpp" -o CMakeFiles/interfaces33.dir/main.cpp.s

# Object files for target interfaces33
interfaces33_OBJECTS = \
"CMakeFiles/interfaces33.dir/imu.cpp.o" \
"CMakeFiles/interfaces33.dir/main.cpp.o"

# External object files for target interfaces33
interfaces33_EXTERNAL_OBJECTS =

interfaces33: CMakeFiles/interfaces33.dir/imu.cpp.o
interfaces33: CMakeFiles/interfaces33.dir/main.cpp.o
interfaces33: CMakeFiles/interfaces33.dir/build.make
interfaces33: CMakeFiles/interfaces33.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable interfaces33"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interfaces33.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interfaces33.dir/build: interfaces33

.PHONY : CMakeFiles/interfaces33.dir/build

CMakeFiles/interfaces33.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interfaces33.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interfaces33.dir/clean

CMakeFiles/interfaces33.dir/depend:
	cd "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33" "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33" "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug" "/run/media/metalleg/Local disk/Documents/CLionProjects/interfaces33/cmake-build-debug/CMakeFiles/interfaces33.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/interfaces33.dir/depend

