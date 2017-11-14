cmake_minimum_required(VERSION 2.8.3)
project(bebop_gazebo)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf
    nav_msgs
)
catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(bebop_odom_to_tf src/bebop_odom_to_tf.cpp)

target_link_libraries(bebop_odom_to_tf
    ${catkin_LIBRARIES}
)