cmake_minimum_required(VERSION 3.27)
project(BSkipList)

set(CMAKE_CXX_STANDARD 17)

set(B_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${B_SRC_INCLUDE_DIR})

file(GLOB SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp")

#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#
#add_library(BSkipList ${SRC_LIST})
#
#link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(test test.cpp)

#target_link_libraries(test BSkipList)
