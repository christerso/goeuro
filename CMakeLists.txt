cmake_minimum_required(VERSION 2.8.7)

project(goeuro)
set (CMAKE_CXX_STANDARD 11)
################################
# Sources
################################
add_subdirectory(src)

################################
# Third-party libraries
################################
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/pistache)

