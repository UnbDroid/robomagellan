# Install script for directory: /home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/conversor_mapa

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/install")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/conversor_mapa/catkin_generated/installspace/conversor_mapa.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/conversor_mapa/cmake" TYPE FILE FILES
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/conversor_mapa/catkin_generated/installspace/conversor_mapaConfig.cmake"
    "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/build/conversor_mapa/catkin_generated/installspace/conversor_mapaConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/conversor_mapa" TYPE FILE FILES "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/conversor_mapa/package.xml")
endif()

