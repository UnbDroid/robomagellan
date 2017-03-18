# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "raspberry_msgs: 12 messages, 0 services")

set(MSG_I_FLAGS "-Iraspberry_msgs:/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(raspberry_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg" NAME_WE)
add_custom_target(_raspberry_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "raspberry_msgs" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_cpp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(raspberry_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(raspberry_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(raspberry_msgs_generate_messages raspberry_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_cpp _raspberry_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(raspberry_msgs_gencpp)
add_dependencies(raspberry_msgs_gencpp raspberry_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS raspberry_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_lisp(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(raspberry_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(raspberry_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(raspberry_msgs_generate_messages raspberry_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_lisp _raspberry_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(raspberry_msgs_genlisp)
add_dependencies(raspberry_msgs_genlisp raspberry_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS raspberry_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)
_generate_msg_py(raspberry_msgs
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(raspberry_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(raspberry_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(raspberry_msgs_generate_messages raspberry_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt16.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_BUZZ/src/raspberry_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(raspberry_msgs_generate_messages_py _raspberry_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(raspberry_msgs_genpy)
add_dependencies(raspberry_msgs_genpy raspberry_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS raspberry_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/raspberry_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(raspberry_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/raspberry_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(raspberry_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/raspberry_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(raspberry_msgs_generate_messages_py std_msgs_generate_messages_py)
