# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build

# Include any dependencies generated for this target.
include arduino_handler/CMakeFiles/arduino_handler.dir/depend.make

# Include the progress variables for this target.
include arduino_handler/CMakeFiles/arduino_handler.dir/progress.make

# Include the compile flags for this target's objects.
include arduino_handler/CMakeFiles/arduino_handler.dir/flags.make

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o: arduino_handler/CMakeFiles/arduino_handler.dir/flags.make
arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o: /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_handler/src/arduino_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o"
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o -c /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_handler/src/arduino_handler.cpp

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.i"
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_handler/src/arduino_handler.cpp > CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.i

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.s"
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_handler/src/arduino_handler.cpp -o CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.s

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.requires:

.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.requires

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.provides: arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.requires
	$(MAKE) -f arduino_handler/CMakeFiles/arduino_handler.dir/build.make arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.provides.build
.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.provides

arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.provides.build: arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o


# Object files for target arduino_handler
arduino_handler_OBJECTS = \
"CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o"

# External object files for target arduino_handler
arduino_handler_EXTERNAL_OBJECTS =

/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: arduino_handler/CMakeFiles/arduino_handler.dir/build.make
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf2_ros.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libactionlib.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libmessage_filters.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libroscpp.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libxmlrpcpp.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf2.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/librosconsole.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/librosconsole_log4cxx.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /home/pi/Documents/desenvolvimentoRos/devel/lib/librosconsole_backend_interface.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /opt/ros/indigo/lib/librostime.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /opt/ros/indigo/lib/libcpp_common.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler: arduino_handler/CMakeFiles/arduino_handler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler"
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arduino_handler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
arduino_handler/CMakeFiles/arduino_handler.dir/build: /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/devel/lib/arduino_handler/arduino_handler

.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/build

arduino_handler/CMakeFiles/arduino_handler.dir/requires: arduino_handler/CMakeFiles/arduino_handler.dir/src/arduino_handler.cpp.o.requires

.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/requires

arduino_handler/CMakeFiles/arduino_handler.dir/clean:
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler && $(CMAKE_COMMAND) -P CMakeFiles/arduino_handler.dir/cmake_clean.cmake
.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/clean

arduino_handler/CMakeFiles/arduino_handler.dir/depend:
	cd /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/arduino_handler /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/arduino_handler/CMakeFiles/arduino_handler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : arduino_handler/CMakeFiles/arduino_handler.dir/depend
