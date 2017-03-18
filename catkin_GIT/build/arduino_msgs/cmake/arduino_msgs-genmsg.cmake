# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "arduino_msgs: 11 messages, 0 services")

set(MSG_I_FLAGS "-Iarduino_msgs:/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(arduino_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg" NAME_WE)
add_custom_target(_arduino_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arduino_msgs" "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_cpp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(arduino_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(arduino_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(arduino_msgs_generate_messages arduino_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_cpp _arduino_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arduino_msgs_gencpp)
add_dependencies(arduino_msgs_gencpp arduino_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arduino_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)
_generate_msg_lisp(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(arduino_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(arduino_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(arduino_msgs_generate_messages arduino_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_lisp _arduino_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arduino_msgs_genlisp)
add_dependencies(arduino_msgs_genlisp arduino_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arduino_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)
_generate_msg_py(arduino_msgs
  "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(arduino_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(arduino_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(arduino_msgs_generate_messages arduino_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedFloat32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint32.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedChar.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedBool.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedString.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedInt8.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/catkin_GIT/src/arduino_msgs/msg/StampedUint64.msg" NAME_WE)
add_dependencies(arduino_msgs_generate_messages_py _arduino_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arduino_msgs_genpy)
add_dependencies(arduino_msgs_genpy arduino_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arduino_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arduino_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(arduino_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arduino_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(arduino_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arduino_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(arduino_msgs_generate_messages_py std_msgs_generate_messages_py)
