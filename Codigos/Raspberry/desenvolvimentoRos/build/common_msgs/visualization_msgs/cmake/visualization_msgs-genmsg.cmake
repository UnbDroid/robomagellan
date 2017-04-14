# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "visualization_msgs: 10 messages, 0 services")

set(MSG_I_FLAGS "-Ivisualization_msgs:/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg;-Igeometry_msgs:/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(visualization_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" "visualization_msgs/Marker:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" "visualization_msgs/InteractiveMarker:visualization_msgs/InteractiveMarkerPose:visualization_msgs/MenuEntry:geometry_msgs/Point:geometry_msgs/Quaternion:visualization_msgs/InteractiveMarkerControl:visualization_msgs/Marker:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" "geometry_msgs/Point:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" "geometry_msgs/Point:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg" "visualization_msgs/Marker:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" "geometry_msgs/Quaternion:visualization_msgs/MenuEntry:geometry_msgs/Point:visualization_msgs/InteractiveMarkerControl:visualization_msgs/Marker:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg" "geometry_msgs/Quaternion:geometry_msgs/Point:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" "visualization_msgs/InteractiveMarker:visualization_msgs/MenuEntry:geometry_msgs/Point:geometry_msgs/Quaternion:visualization_msgs/InteractiveMarkerControl:visualization_msgs/Marker:std_msgs/Header:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg" "std_msgs/ColorRGBA:geometry_msgs/Point:std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(visualization_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_gencpp)
add_dependencies(visualization_msgs_gencpp visualization_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(visualization_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_genlisp)
add_dependencies(visualization_msgs_genlisp visualization_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Quaternion.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Pose.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pi/Documents/desenvolvimentoRos/src/common_msgs/geometry_msgs/msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(visualization_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/desenvolvimentoRos/src/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_genpy)
add_dependencies(visualization_msgs_genpy visualization_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(visualization_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(visualization_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(visualization_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(visualization_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(visualization_msgs_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(visualization_msgs_generate_messages_py std_msgs_generate_messages_py)
