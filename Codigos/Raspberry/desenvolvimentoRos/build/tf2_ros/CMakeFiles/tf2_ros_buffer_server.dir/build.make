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
include tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/depend.make

# Include the progress variables for this target.
include tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/progress.make

# Include the compile flags for this target's objects.
include tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/flags.make

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/flags.make
tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o: /home/pi/Documents/desenvolvimentoRos/src/tf2_ros/src/buffer_server_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/Documents/desenvolvimentoRos/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2_ros && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o -c /home/pi/Documents/desenvolvimentoRos/src/tf2_ros/src/buffer_server_main.cpp

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.i"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2_ros && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/Documents/desenvolvimentoRos/src/tf2_ros/src/buffer_server_main.cpp > CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.i

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.s"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2_ros && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/Documents/desenvolvimentoRos/src/tf2_ros/src/buffer_server_main.cpp -o CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.s

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.requires:
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.requires

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.provides: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.requires
	$(MAKE) -f tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/build.make tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.provides.build
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.provides

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.provides.build: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o

# Object files for target tf2_ros_buffer_server
tf2_ros_buffer_server_OBJECTS = \
"CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o"

# External object files for target tf2_ros_buffer_server
tf2_ros_buffer_server_EXTERNAL_OBJECTS =

/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/build.make
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf2_ros.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /home/pi/Documents/desenvolvimentoRos/devel/lib/libactionlib.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libmessage_filters.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libroscpp.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/librosconsole.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /home/pi/Documents/desenvolvimentoRos/devel/lib/libtf2.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/librostime.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libcpp_common.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/librostime.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /opt/ros/indigo/lib/libcpp_common.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server"
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2_ros && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tf2_ros_buffer_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/build: /home/pi/Documents/desenvolvimentoRos/devel/lib/tf2_ros/buffer_server
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/build

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/requires: tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/src/buffer_server_main.cpp.o.requires
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/requires

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/clean:
	cd /home/pi/Documents/desenvolvimentoRos/build/tf2_ros && $(CMAKE_COMMAND) -P CMakeFiles/tf2_ros_buffer_server.dir/cmake_clean.cmake
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/clean

tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/depend:
	cd /home/pi/Documents/desenvolvimentoRos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/desenvolvimentoRos/src /home/pi/Documents/desenvolvimentoRos/src/tf2_ros /home/pi/Documents/desenvolvimentoRos/build /home/pi/Documents/desenvolvimentoRos/build/tf2_ros /home/pi/Documents/desenvolvimentoRos/build/tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tf2_ros/CMakeFiles/tf2_ros_buffer_server.dir/depend

