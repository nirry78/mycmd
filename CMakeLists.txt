cmake_minimum_required(VERSION 3.5)

project (mycmd)

set(SRCS
    MyCommand.cpp)

add_definitions("-std=c++17")

include_directories(.)

add_executable(mycmd ${SRCS})
target_link_libraries(mycmd readline)