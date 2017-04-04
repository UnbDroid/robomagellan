# Install script for directory: /home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization_msgs/msg" TYPE FILE FILES
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization_msgs/cmake" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/catkin_generated/installspace/visualization_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/include/visualization_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/share/common-lisp/ros/visualization_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/visualization_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/visualization_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/catkin_generated/installspace/visualization_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization_msgs/cmake" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/catkin_generated/installspace/visualization_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization_msgs/cmake" TYPE FILE FILES
    "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/catkin_generated/installspace/visualization_msgsConfig.cmake"
    "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/visualization_msgs/catkin_generated/installspace/visualization_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization_msgs" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/package.xml")
endif()

