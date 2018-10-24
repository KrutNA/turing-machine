cmake_minimum_required(VERSION 3.10)
project(turing_machine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_SOURCE_DIR ./)
set(INCLUDE_DIR ./include)
set(SRC_DIR ./src)
set(EXECUTABLE_NAME turing-machine)

set(SRCS
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/input-validator.cpp
        ${SRC_DIR}/turing-machine.cpp
        )

include_directories(${INCLUDE_DIR})

add_executable(${EXECUTABLE_NAME} ${SRCS})

