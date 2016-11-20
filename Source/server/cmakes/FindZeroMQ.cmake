##
## Created by Gaston Siffert.
##

IF (UNIX OR APPLE)

    # Include dir
    find_path(ZMQ_INCLUDE_DIR
            NAMES zmq.h
            PATHS ${ZEROMQ_ROOT}/include /usr/local/include
            )

    # Finally the library itself
    find_library(ZMQ_LIBRARY
            NAMES zmq
            PATHS ${ZEROMQ_ROOT}/lib /usr/local/lib
            )

ENDIF()