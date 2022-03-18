cmake_minimum_required(VERSION 3.0.2)
project(pepper_behaviour_node_cpp)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  naoqi_libqi
  naoqi_libqicore
  pepper_behaviour_srvs
  roscpp
)

set(
  SERVICES_SRC
  src/behaviour.cpp
)

# use catkin if qibuild is not found
if(DEFINED qibuild_DIR)
  find_package(qibuild QUIET)
else()
  find_package(catkin QUIET)
  include(CMakeLists_catkin.txt)
  return()
endif()


find_package(qimodule)

include_directories( include )

qi_create_module(pepper_behaviour
    src/behaviour.cpp
  SHARED
)
#qi_stage_lib(pepper_behaviour_module)

#qi_create_lib(
#  pepper_behaviour_node_cpp
#  SHARED
#  ${SERVICES_SRC}
#)
#qi_use_lib(pepper_behaviour_node_cpp QICORE QI ROS)
#qi_stage_lib(pepper_behaviour_node_cpp)

#target_link_libraries(pepper_behaviour_node_cpp ${catkin_LIBRARIES})
#qi_create_bin(pepper_behaviour src/behaviour.cpp)




#add_executable(pepper_behaviour src/behaviour.cpp)
#target_link_libraries(pepper_behaviour ${catkin_LIBRARIES})
#add_dependencies(pepper_behaviour pepper_behaviour_srvs_gencpp)
