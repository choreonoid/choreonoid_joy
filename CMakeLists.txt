cmake_minimum_required(VERSION 2.8.3)
project(choreonoid_joy)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  choreonoid
)

catkin_package(
  CATKIN_DEPENDS choreonoid
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${CHOREONOID_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/choreonoid_joy_node.cpp)

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${CHOREONOID_UTIL_LIBRARIES} ${catkin_LIBRARIES}
  )

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )
