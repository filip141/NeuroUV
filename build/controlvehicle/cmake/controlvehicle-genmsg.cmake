# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "controlvehicle: 4 messages, 0 services")

set(MSG_I_FLAGS "-Icontrolvehicle:/home/pi/catkin_ws/src/controlvehicle/msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(controlvehicle_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg" NAME_WE)
add_custom_target(_controlvehicle_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "controlvehicle" "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg" ""
)

get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg" NAME_WE)
add_custom_target(_controlvehicle_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "controlvehicle" "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg" ""
)

get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg" NAME_WE)
add_custom_target(_controlvehicle_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "controlvehicle" "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg" ""
)

get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg" NAME_WE)
add_custom_target(_controlvehicle_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "controlvehicle" "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
)
_generate_msg_cpp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
)
_generate_msg_cpp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
)
_generate_msg_cpp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
)

### Generating Services

### Generating Module File
_generate_module_cpp(controlvehicle
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(controlvehicle_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(controlvehicle_generate_messages controlvehicle_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_cpp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_cpp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_cpp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_cpp _controlvehicle_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(controlvehicle_gencpp)
add_dependencies(controlvehicle_gencpp controlvehicle_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS controlvehicle_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
)
_generate_msg_lisp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
)
_generate_msg_lisp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
)
_generate_msg_lisp(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
)

### Generating Services

### Generating Module File
_generate_module_lisp(controlvehicle
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(controlvehicle_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(controlvehicle_generate_messages controlvehicle_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_lisp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_lisp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_lisp _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_lisp _controlvehicle_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(controlvehicle_genlisp)
add_dependencies(controlvehicle_genlisp controlvehicle_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS controlvehicle_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
)
_generate_msg_py(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
)
_generate_msg_py(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
)
_generate_msg_py(controlvehicle
  "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
)

### Generating Services

### Generating Module File
_generate_module_py(controlvehicle
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(controlvehicle_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(controlvehicle_generate_messages controlvehicle_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/joy_control_msg.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_py _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/temperature.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_py _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/Maxsonar.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_py _controlvehicle_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/catkin_ws/src/controlvehicle/msg/ardu_imu.msg" NAME_WE)
add_dependencies(controlvehicle_generate_messages_py _controlvehicle_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(controlvehicle_genpy)
add_dependencies(controlvehicle_genpy controlvehicle_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS controlvehicle_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/controlvehicle
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(controlvehicle_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(controlvehicle_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/controlvehicle
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(controlvehicle_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(controlvehicle_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/controlvehicle
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(controlvehicle_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(controlvehicle_generate_messages_py std_msgs_generate_messages_py)
