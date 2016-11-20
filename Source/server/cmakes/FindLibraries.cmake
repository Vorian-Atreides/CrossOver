##
## Created by Gaston Siffert
##

find_package(ZeroMQPP REQUIRED)
find_package(ZeroMQ REQUIRED)
find_package(Proto REQUIRED)
find_package(MySqlConn REQUIRED)
find_package(CurlLib REQUIRED)

include_directories(
        ${ZeroMQPP_INCLUDE_DIR}
        ${ZMQ_INCLUDE_DIR}
        ${PROTOBUF_INCLUDE_DIRS}
        ${MySQL_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
)
list(APPEND Libraries
        ${ZeroMQPP_LIBRARY}
        ${ZMQ_LIBRARY}
        ${PROTOBUF_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${MySQL_LIBRARY}
        ${CURL_LIBRARIES}
)