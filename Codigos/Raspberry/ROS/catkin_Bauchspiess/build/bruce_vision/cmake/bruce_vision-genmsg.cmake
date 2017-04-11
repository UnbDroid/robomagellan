# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "bruce_vision: 1 messages, 1 services")

set(MSG_I_FLAGS "-Ibruce_vision:/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(bruce_vision_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg" NAME_WE)
add_custom_target(_bruce_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bruce_vision" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg" ""
)

get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv" NAME_WE)
add_custom_target(_bruce_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bruce_vision" "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bruce_vision
)

### Generating Services
_generate_srv_cpp(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bruce_vision
)

### Generating Module File
_generate_module_cpp(bruce_vision
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bruce_vision
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(bruce_vision_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(bruce_vision_generate_messages bruce_vision_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg" NAME_WE)
add_dependencies(bruce_vision_generate_messages_cpp _bruce_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bruce_vision_generate_messages_cpp _bruce_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bruce_vision_gencpp)
add_dependencies(bruce_vision_gencpp bruce_vision_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bruce_vision_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bruce_vision
)

### Generating Services
_generate_srv_lisp(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bruce_vision
)

### Generating Module File
_generate_module_lisp(bruce_vision
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bruce_vision
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(bruce_vision_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(bruce_vision_generate_messages bruce_vision_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg" NAME_WE)
add_dependencies(bruce_vision_generate_messages_lisp _bruce_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bruce_vision_generate_messages_lisp _bruce_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bruce_vision_genlisp)
add_dependencies(bruce_vision_genlisp bruce_vision_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bruce_vision_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision
)

### Generating Services
_generate_srv_py(bruce_vision
  "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision
)

### Generating Module File
_generate_module_py(bruce_vision
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(bruce_vision_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(bruce_vision_generate_messages bruce_vision_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/msg/Num.msg" NAME_WE)
add_dependencies(bruce_vision_generate_messages_py _bruce_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/Documents/robomagellan/Codigos/Raspberry/ROS/catkin_Bauchspiess/src/bruce_vision/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bruce_vision_generate_messages_py _bruce_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bruce_vision_genpy)
add_dependencies(bruce_vision_genpy bruce_vision_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bruce_vision_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bruce_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bruce_vision
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(bruce_vision_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bruce_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bruce_vision
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(bruce_vision_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bruce_vision
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(bruce_vision_generate_messages_py std_msgs_generate_messages_py)
endif()
