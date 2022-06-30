# target_link_directories: versionadded:: 3.13
cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_external_libs)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)

include(Dependency.cmake)

# add include/lib option to our project
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# build dependencies first
add_dependencies(${PROJECT_NAME} ${DEP_LIST})