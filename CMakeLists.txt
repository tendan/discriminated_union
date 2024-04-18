cmake_minimum_required(VERSION 3.24)
project(discriminated_union)

set(INCLUDE_DIR include)

set(SOURCE_DIR src)

set(SOURCE_FILES
        main.cpp
        ${SOURCE_DIR}/Result.cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(discriminated_union ${SOURCE_FILES})
target_include_directories(discriminated_union PRIVATE ${INCLUDE_DIR})
