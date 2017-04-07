# Install script for directory: /home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs

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
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/safe_execute_install.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs/msg" TYPE FILE FILES
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/BatteryState.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/CameraInfo.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/ChannelFloat32.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/CompressedImage.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/FluidPressure.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Illuminance.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Image.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Imu.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/JointState.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Joy.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/JoyFeedback.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/JoyFeedbackArray.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/LaserEcho.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/LaserScan.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/MagneticField.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/MultiDOFJointState.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/MultiEchoLaserScan.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/NavSatFix.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/NavSatStatus.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/PointCloud.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/PointCloud2.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/PointField.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Range.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/RegionOfInterest.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/RelativeHumidity.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/Temperature.msg"
    "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/msg/TimeReference.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs/srv" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/srv/SetCameraInfo.srv")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs/cmake" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/installspace/sensor_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/include/sensor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/share/common-lisp/ros/sensor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/sensor_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/sensor_msgs" REGEX "/\\_\\_init\\_\\_\\.py$" EXCLUDE REGEX "/\\_\\_init\\_\\_\\.pyc$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/sensor_msgs" FILES_MATCHING REGEX "/home/pi/Documents/desenvolvimentoRos/devel/lib/python2.7/dist-packages/sensor_msgs/.+/__init__.pyc?$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/installspace/sensor_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs/cmake" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/installspace/sensor_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs/cmake" TYPE FILE FILES
    "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/installspace/sensor_msgsConfig.cmake"
    "/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/catkin_generated/installspace/sensor_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sensor_msgs" TYPE FILE FILES "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/sensor_msgs" TYPE DIRECTORY FILES "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/sensor_msgs/include/sensor_msgs/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pi/Documents/desenvolvimentoRos/build/common_msgs/sensor_msgs/test/cmake_install.cmake")

endif()

