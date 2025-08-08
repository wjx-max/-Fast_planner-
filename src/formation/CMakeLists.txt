################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(formation)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
  sensor_msgs
  nav_msgs
  geometry_msgs
  std_msgs
  message_generation
)

################################################################################
# Setup for python modules and scripts
################################################################################

################################################################################
# Declare ROS messages, services and actions
################################################################################

################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp   
)

################################################################################
# Build
################################################################################
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(test_node src/test.cpp)
target_link_libraries(test_node ${catkin_LIBRARIES})

add_executable(tb3_all_assemble_node src/tb3_all_assemble.cpp)
target_link_libraries(tb3_all_assemble_node ${catkin_LIBRARIES})

add_executable(tb3_all_assembleNew_node src/tb3_all_assembleNew.cpp)
target_link_libraries(tb3_all_assembleNew_node ${catkin_LIBRARIES})

add_executable(Consisience_node src/Consisience.cpp)
target_link_libraries(Consisience_node ${catkin_LIBRARIES})

add_executable(Consensus_node src/Consensus.cpp)
target_link_libraries(Consensus_node ${catkin_LIBRARIES})


add_executable(tb3_all_randomRun_node src/tb3_all_randomRun.cpp)
target_link_libraries(tb3_all_randomRun_node ${catkin_LIBRARIES})

add_executable(tb3_all_openroad_node src/tb3_all_openroad.cpp)
target_link_libraries(tb3_all_openroad_node ${catkin_LIBRARIES})

add_executable(tb3_all_closeroad_node src/tb3_all_closeroad.cpp)
target_link_libraries(tb3_all_closeroad_node ${catkin_LIBRARIES})


add_executable(tb3_all_move_node src/tb3_all_move.cpp)
target_link_libraries(tb3_all_move_node ${catkin_LIBRARIES})

add_executable(tb3_all_moveRectangle_node src/tb3_all_moveRectangle.cpp)
target_link_libraries(tb3_all_moveRectangle_node ${catkin_LIBRARIES})

add_executable(tb3_all_moveTriangle_node src/tb3_all_moveTriangle.cpp)
target_link_libraries(tb3_all_moveTriangle_node ${catkin_LIBRARIES})


add_executable(tb3_all_moveOne_node src/tb3_all_moveOne.cpp)
target_link_libraries(tb3_all_moveOne_node ${catkin_LIBRARIES})



################################################################################
# Install
################################################################################

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

################################################################################
# Test
################################################################################
