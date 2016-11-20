##
## Created by Gaston Siffert
##

cmake_minimum_required(VERSION 3.0)
set(ProjectName server)

## Define the project
project(${ProjectName} C CXX)
set(CMAKE_BUILD_TYPE Debug)

## Add the sources and the libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmakes)
find_package(ProjectFiles REQUIRED)
find_package(Libraries REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++11 -pthread")

IF (Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF()

## Build the project and link the libraries
add_executable(${ProjectName}
               ${Sources}
               ${Protos}
               ${Includes})
set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 11)
target_link_libraries(${ProjectName} ${Libraries})

# Add test
# add_executable(${ProjectName}_test
#                ${SourceDir}/AlertWorker.cpp
#                ${IncludeDir}/AlertWorker.h
#                ${Protos}
#                ${Tests})
# target_link_libraries(${ProjectName}_test ${Libraries})
# enable_testing()

# add_test(

# )