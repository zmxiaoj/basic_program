cmake_minimum_required(VERSION 2.6)
project(basic_program)

add_compile_options(-std=c++11)
SET(CMAKE_BUILD_TYPE Release)
# SET(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV 4 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    # ${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME}_lib SHARED
    src/test_eigen.cpp
)

target_link_libraries(${PROJECT_NAME}_lib
    ${EIGEN3_LIBS}
    ${OpenCV_LIBS}
)


# test line ransac
add_executable(test_eigen
    src/test_eigen.cpp)
target_link_libraries(test_eigen
	${PROJECT_NAME}_lib
)