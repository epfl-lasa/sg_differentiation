cmake_minimum_required(VERSION 2.8.3)
project(sg_differentiation)

####################### CMAKE STUFF ##################
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/test)
set(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib )
set(LIB_INSTALL_PATH        ${CMAKE_INSTALL_PREFIX}lib/) 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package (Eigen3 REQUIRED) 
include_directories(include)
 
FILE(GLOB SRC_FILES src/sg_filter.cpp)
FILE(GLOB HEADER_FILES include/sg_filter.h)


add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
install(TARGETS ${PROJECT_NAME} DESTINATION lib EXPORT ${PROJECT_NAME}-targets)
install(EXPORT ${PROJECT_NAME}-targets DESTINATION lib/${PROJECT_NAME})
target_link_libraries ( ${PROJECT_NAME} pthread)

###### GTEST STUFF ######
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${PROJECT_NAME}-test
  test/test_sg_differentiation.cpp
  ${WORKING_DIR} ${PROJECT_SOURCE_DIR}/test)
target_link_libraries(${PROJECT_NAME}-test 
${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
add_test(AllTestsInSG ${PROJECT_NAME}-test)

####################### CATKIN STUFF ##################
#find_package(catkin REQUIRED)
#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES sg_differentiation
#)

#include_directories(include)

## Declare a C++ library
# add_library(sg_differentiation
#   src/sg_filter.cpp include/sg_filter.h
# )

## Add gtest based cpp test target and link libraries
#catkin_add_gtest(${PROJECT_NAME}-test
#  test/test_sg_differentiation.cpp
#  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
#if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
#endif()

