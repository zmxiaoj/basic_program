cmake_minimum_required(VERSION 2.6)
project(basic_program)

add_compile_options(-std=c++11)
SET(CMAKE_BUILD_TYPE Release)
# SET(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV 4 REQUIRED)
find_package(PCL REQUIRED COMPONENTS common)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
    ${CERES_INCLUDE_DIRS}
)

# 创建一个库（如果有共享代码的话，否则可以省略）
# add_library(${PROJECT_NAME}_common SHARED
#     # 添加这里共享的源文件，如果没有共享代码，则不需要这个库
# )

# target_link_libraries(${PROJECT_NAME}_common
#     ${EIGEN3_LIBS}
#     ${OpenCV_LIBS}
#     ${PCL_LIBRARIES}
# )

link_directories(
    ${PCL_LIBRARY_DIRS}
)

# test eigen 可执行文件
add_executable(test_eigen
    src/eigen/test_eigen.cpp
)
target_link_libraries(test_eigen
    ${EIGEN3_LIBS}
)

add_executable(GN_naive
    src/eigen/GN.cpp
)
target_link_libraries(GN_naive
    ${EIGEN3_LIBS}
)

add_executable(BA_naive
    src/eigen/BA.cpp
)
target_link_libraries(BA_naive
    ${EIGEN3_LIBS}
)

# ceres_solver
add_executable(ceres_test
    src/ceres/ceres_test.cpp
)
target_link_libraries(ceres_test
    ${CERES_LIBRARIES}
)

# feature_extraction 可执行文件
add_executable(feature_extraction
    src/opencv/feature_extractor.cpp
)
target_link_libraries(feature_extraction
    ${EIGEN3_LIBS}
    ${OpenCV_LIBS}
)