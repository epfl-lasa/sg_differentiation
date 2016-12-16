cmake_minimum_required(VERSION 2.8.3)
project(sg_differentiation)

####################### CMAKE STUFF ##################
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/test)
set(CMAKE_INSTALL_PREFIX    /usr/)
set(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib )
set(LIB_INSTALL_PATH        ${CMAKE_INSTALL_PREFIX}lib/) 
set(CMAKE_MODULE_PATH       ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(INCLUDE_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/include)    
set(SRC_DIR                 ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -O2 -O3")

set(SGD_INC ${INCLUDE_DIR}/sg_filter.h)

find_package (Eigen3 REQUIRED) 

FILE(GLOB SRC_FILES src/sg_filter.cpp)
FILE(GLOB HEADER_FILES include/sg_filter.h)

include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
target_link_libraries ( ${PROJECT_NAME} pthread)

# INSTALL
message(status "    CMAKE_INSTALL_PREFIX:" ${CMAKE_INSTALL_PREFIX})
install(TARGETS ${PROJECT_NAME} DESTINATION lib EXPORT ${PROJECT_NAME}-targets)
install(EXPORT ${PROJECT_NAME}-targets DESTINATION lib/${PROJECT_NAME})
install(FILES ${SGD_INC} DESTINATION include/)

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

###### Normal Test ######
add_executable(multidim_test
  test/multidim_test.cpp
  ${WORKING_DIR} ${PROJECT_SOURCE_DIR}/test)
target_link_libraries(multidim_test 
${PROJECT_NAME} pthread)


