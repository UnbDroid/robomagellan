# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/pi/Documents/desenvolvimentoRos/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/desenvolvimentoRos/build

# Include any dependencies generated for this target.
include tf2/CMakeFiles/test_simple.dir/depend.make

# Include the progress variables for this target.
include tf2/CMakeFiles/test_simple.dir/progress.make

# Include the compile flags for this target's objects.
include tf2/CMakeFiles/test_simple.dir/flags.make

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o: tf2/CMakeFiles/test_simple.dir/flags.make
tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o: /home/pi/Documents/desenvolvimentoRos/src/tf2/test/simple_tf2_core.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/Documents/desenvolvimentoRos/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o -c /home/pi/Documents/desenvolvimentoRos/src/tf2/test/simple_tf2_core.cpp

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.i"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/Documents/desenvolvimentoRos/src/tf2/test/simple_tf2_core.cpp > CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.i

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.s"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/Documents/desenvolvimentoRos/src/tf2/test/simple_tf2_core.cpp -o CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.s

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.requires:
.PHONY : tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.requires

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.provides: tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.requires
	$(MAKE) -f tf2/CMakeFiles/test_simple.dir/build.make tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.provides.build
.PHONY : tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.provides

tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.provides.build: tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o

# Object files for target test_simple
test_simple_OBJECTS = \
"CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o"

# External object files for target test_simple
test_simple_EXTERNAL_OBJECTS =

/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: tf2/CMakeFiles/test_simple.dir/build.make
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: gtest/libgtest.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf2.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/librostime.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/libcpp_common.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/librostime.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /opt/ros/indigo/lib/libcpp_common.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple: tf2/CMakeFiles/test_simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tf2/CMakeFiles/test_simple.dir/build: /home/pi/Documents/desenvolvimentoRos/devel/lib/tf2/test_simple
.PHONY : tf2/CMakeFiles/test_simple.dir/build

tf2/CMakeFiles/test_simple.dir/requires: tf2/CMakeFiles/test_simple.dir/test/simple_tf2_core.cpp.o.requires
.PHONY : tf2/CMakeFiles/test_simple.dir/requires

tf2/CMakeFiles/test_simple.dir/clean:
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2 && $(CMAKE_COMMAND) -P CMakeFiles/test_simple.dir/cmake_clean.cmake
.PHONY : tf2/CMakeFiles/test_simple.dir/clean

tf2/CMakeFiles/test_simple.dir/depend:
	cd /home/pi/Documents/desenvolvimentoRos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/desenvolvimentoRos/src /home/pi/Documents/desenvolvimentoRos/src/tf2 /home/pi/Documents/desenvolvimentoRos/build /home/pi/Documents/desenvolvimentoRos/build/tf2 /home/pi/Documents/desenvolvimentoRos/build/tf2/CMakeFiles/test_simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tf2/CMakeFiles/test_simple.dir/depend

