cmake_minimum_required(VERSION 2.7)

include_directories(
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/third-party/pistache/include)

set(SOURCE_FILES main.cpp routehandler.cpp busroute.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} net)
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/src)
install(FILES ${CMAKE_BINARY_DIR}/src/resources/bus-routes.txt DESTINATION /etc)
install(TARGETS goeuro DESTINATION bin)
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "christer.soderlund@gmail.com")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "goeuro challange")
INCLUDE(CPack)
