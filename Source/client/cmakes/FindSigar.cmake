##
## Created by Gaston Siffert.
##

IF (UNIX OR APPLE)

    # Include dir
    find_path(SIGAR_INCLUDE_DIR
            NAMES sigar.h
            PATHS ${SIGAR_ROOT}/include /usr/local/include
            )

    # Finally the library itself
    find_library(SIGAR_LIBRARY
            NAMES sigar
            PATHS ${SIGAR_ROOT}/lib /usr/local/lib
            )

ENDIF()