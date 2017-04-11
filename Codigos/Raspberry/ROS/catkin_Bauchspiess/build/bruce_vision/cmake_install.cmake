# Install script for directory: /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/install")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision/msg" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision/srv" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision/cmake" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/build/bruce_vision/catkin_generated/installspace/bruce_vision-msg-paths.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/devel/include/bruce_vision")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/devel/share/common-lisp/ros/bruce_vision")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/devel/lib/python2.7/dist-packages/bruce_vision")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/devel/lib/python2.7/dist-packages/bruce_vision")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/build/bruce_vision/catkin_generated/installspace/bruce_vision.pc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision/cmake" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/build/bruce_vision/catkin_generated/installspace/bruce_vision-msg-extras.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision/cmake" TYPE FILE FILES
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/build/bruce_vision/catkin_generated/installspace/bruce_visionConfig.cmake"
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/build/bruce_vision/catkin_generated/installspace/bruce_visionConfig-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/bruce_vision" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/package.xml")
endif()

