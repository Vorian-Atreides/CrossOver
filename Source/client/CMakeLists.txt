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
               ${Protos})
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 11)
target_link_libraries(${ProjectName} ${Libraries})

## Add tests
add_executable(${ProjectName}_test
               ${SourceDir}/SigarWrapper.cpp
               ${IncludeDir}/SigarWrapper.h
               ${Protos}
               ${Tests})
target_link_libraries(${ProjectName}_test ${Libraries})
enable_testing()

add_test(
    CpuTest
    ${ProjectName}_test
)
add_test(
    MemoryTest
    ${ProjectName}_test
)
add_test(
    ProcessesTest
    ${ProjectName}_test
)