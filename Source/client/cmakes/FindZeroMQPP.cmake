##
## Created by Gaston Siffert.
##

IF (UNIX OR APPLE)

    # Include dir
    find_path(ZeroMQPP_INCLUDE_DIR
            NAMES zmqpp/zmqpp.hpp
            PATHS ${ZEROMQPP_ROOT}/include /usr/local/include
            )

    # Finally the library itself
    find_library(ZeroMQPP_LIBRARY
            NAMES zmqpp
            PATHS ${ZEROMQPP_ROOT}/lib /usr/local/lib
            )

ENDIF()