##
## Created by Gaston Siffert.
##

set(TestDir ${CMAKE_SOURCE_DIR}/tests)
set(SourceDir ${CMAKE_SOURCE_DIR}/sources)
set(IncludeDir ${CMAKE_SOURCE_DIR}/includes)

file(GLOB_RECURSE Tests ${TestDir}/*.cpp)
file(GLOB_RECURSE Sources ${SourceDir}/*.cpp)
file(GLOB_RECURSE Protos ${SourceDir}/*.cc)
file(GLOB_RECURSE Includes ${IncludeDir}/*.h)

include_directories(${IncludeDir})
