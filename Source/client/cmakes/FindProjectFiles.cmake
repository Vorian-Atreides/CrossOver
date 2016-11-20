##
## Created by Gaston Siffert.
##

set(SourceDir ${CMAKE_SOURCE_DIR}/sources)
set(IncludeDir ${CMAKE_SOURCE_DIR}/includes)

file(GLOB_RECURSE Sources ${SourceDir}/*.cpp)
file(GLOB_RECURSE Protos ${SourceDir}/*.cc)
file(GLOB_RECURSE Includes ${IncludeDir}/*.h)

include_directories(${IncludeDir})
