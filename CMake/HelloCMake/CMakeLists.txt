# VERSION >= 3.11
cmake_minimum_required(VERSION 3.11)

# set variables
# PROJECT_NAME = "hello_cmake"
# CMAKE_CXX_STANDARD = "17"
set(PROJECT_NAME hello_cmake)
set(CMAKE_CXX_STANDARD 17)

# use variables
# project(hello_cmake)
# add_executable(add_executable src/HelloCMake.cpp)
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/HelloCMake.cpp)