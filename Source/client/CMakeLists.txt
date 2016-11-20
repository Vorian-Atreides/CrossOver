##
## Created by Gaston Siffert
##

cmake_minimum_required(VERSION 3.0)
set(ProjectName client)

SET(TEST false CACHE BOOL "Embbed the tests")
message(STATUS ${TEST})
# add_executable(${ProjectName} ${CMAKE_SOURCE_DIR}/tests/test.cpp)
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIR})

## Define the project
project(${ProjectName} C CXX)
set(CMAKE_BUILD_TYPE Debug)

## Add the sources and the libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmakes)
find_package(ProjectFiles REQUIRED)
find_package(Libraries REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++11")

IF (Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

## Build the project and link the libraries
add_executable(${ProjectName}
               ${Sources}
               ${Includes}
               ${Protos}
               ${CMAKE_SOURCE_DIR}/tests/example.cpp)
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 11)
target_link_libraries(${ProjectName} ${Libraries})

enable_testing()
GTEST_ADD_TESTS(${ProjectName} "" ${CMAKE_SOURCE_DIR}/tests/example.cpp)
add_test(
    ${CMAKE_SOURCE_DIR}/tests/example.cpp
    ${ProjectName}
)