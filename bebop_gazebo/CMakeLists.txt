cmake_minimum_required(VERSION 2.8.3)
project(bebop_gazebo)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  geometry_msgs
  hector_quadrotor_interface
  hector_quadrotor_actions
  hector_uav_msgs
  roscpp
  tf2
  tf2_geometry_msgs
  )
include_directories(${catkin_INCLUDE_DIRS})

catkin_package(
    LIBRARIES 
    CATKIN_DEPENDS roscpp
    DEPENDS
)

add_executable(emergency_action
  src/emergency_action.cpp
  )
target_link_libraries(emergency_action ${catkin_LIBRARIES})
add_dependencies(emergency_action ${catkin_EXPORTED_TARGETS})

