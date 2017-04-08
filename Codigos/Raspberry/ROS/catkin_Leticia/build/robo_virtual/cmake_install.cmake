# Install script for directory: /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/src/robo_virtual

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/install")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robo_virtual/msg" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/src/robo_virtual/msg/Posicao.msg")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robo_virtual/cmake" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/build/robo_virtual/catkin_generated/installspace/robo_virtual-msg-paths.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/devel/include/robo_virtual")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/devel/share/common-lisp/ros/robo_virtual")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/devel/lib/python2.7/dist-packages/robo_virtual")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/devel/lib/python2.7/dist-packages/robo_virtual")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/build/robo_virtual/catkin_generated/installspace/robo_virtual.pc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robo_virtual/cmake" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/build/robo_virtual/catkin_generated/installspace/robo_virtual-msg-extras.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robo_virtual/cmake" TYPE FILE FILES
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/build/robo_virtual/catkin_generated/installspace/robo_virtualConfig.cmake"
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/build/robo_virtual/catkin_generated/installspace/robo_virtualConfig-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robo_virtual" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Leticia/src/robo_virtual/package.xml")
endif()

