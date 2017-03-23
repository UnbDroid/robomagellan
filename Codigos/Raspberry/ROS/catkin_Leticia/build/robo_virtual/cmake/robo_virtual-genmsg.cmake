# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "robo_virtual: 1 messages, 0 services")

set(MSG_I_FLAGS "-Irobo_virtual:/home/leticia/catkin_Leticia/src/robo_virtual/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(robo_virtual_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg" NAME_WE)
add_custom_target(_robo_virtual_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robo_virtual" "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(robo_virtual
  "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robo_virtual
)

### Generating Services

### Generating Module File
_generate_module_cpp(robo_virtual
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robo_virtual
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(robo_virtual_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(robo_virtual_generate_messages robo_virtual_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg" NAME_WE)
add_dependencies(robo_virtual_generate_messages_cpp _robo_virtual_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robo_virtual_gencpp)
add_dependencies(robo_virtual_gencpp robo_virtual_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robo_virtual_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(robo_virtual
  "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robo_virtual
)

### Generating Services

### Generating Module File
_generate_module_lisp(robo_virtual
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robo_virtual
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(robo_virtual_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(robo_virtual_generate_messages robo_virtual_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg" NAME_WE)
add_dependencies(robo_virtual_generate_messages_lisp _robo_virtual_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robo_virtual_genlisp)
add_dependencies(robo_virtual_genlisp robo_virtual_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robo_virtual_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(robo_virtual
  "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robo_virtual
)

### Generating Services

### Generating Module File
_generate_module_py(robo_virtual
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robo_virtual
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(robo_virtual_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(robo_virtual_generate_messages robo_virtual_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/leticia/catkin_Leticia/src/robo_virtual/msg/Posicao.msg" NAME_WE)
add_dependencies(robo_virtual_generate_messages_py _robo_virtual_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robo_virtual_genpy)
add_dependencies(robo_virtual_genpy robo_virtual_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robo_virtual_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robo_virtual)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robo_virtual
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(robo_virtual_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robo_virtual)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robo_virtual
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(robo_virtual_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robo_virtual)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robo_virtual\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robo_virtual
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(robo_virtual_generate_messages_py std_msgs_generate_messages_py)
