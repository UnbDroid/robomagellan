# Install script for directory: /home/pi/Documents/desenvolvimentoRos/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/Documents/desenvolvimentoRos/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE PROGRAM FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/_setup_util.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE PROGRAM FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/env.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/setup.bash")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/setup.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/setup.zsh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/Documents/desenvolvimentoRos/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/Documents/desenvolvimentoRos/install" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pi/Documents/desenvolvimentoRos/build/gtest/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/common_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_arduino/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_mbed/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_python/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_tivac/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_xbee/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_client/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/angles/angles/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/actionlib_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/diagnostic_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/geometry_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/nav_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/shape_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/stereo_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/tf2_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/tf2/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/trajectory_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/teste/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/tf2_py/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/actionlib/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_server/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/tf2_ros/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/tf/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_embeddedlinux/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_test/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/rosserial/rosserial_windows/cmake_install.cmake")
  include("/home/pi/Documents/desenvolvimentoRos/build/ultrassom/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/pi/Documents/desenvolvimentoRos/build/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/pi/Documents/desenvolvimentoRos/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
