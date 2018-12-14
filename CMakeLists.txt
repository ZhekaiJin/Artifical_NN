cmake_minimum_required(VERSION 3.8)
project(ANN)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(TRIAN_SOURCE_FILES src/ANN.cpp src/ANN_trian.cpp)

set(TEST_SOURCE_FILES  src/ANN.cpp src/ANN_test.cpp)

add_executable(ANN_trian ${TRIAN_SOURCE_FILES} include/ANN.h)
add_executable(ANN_test ${TEST_SOURCE_FILES})