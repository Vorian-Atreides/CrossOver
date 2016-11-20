##
## Created by Gaston Siffert.
##

IF (UNIX OR APPLE)

    # Include dir
    find_path(GTEST_INCLUDE_DIR
            NAMES gtest.h
            PATHS ${GTEST_ROOT}/include /usr/local/include/gtest
            )

    # Finally the library itself
    find_library(GTEST_LIBRARY
            NAMES gtest
            PATHS ${GTEST_ROOT}/lib /usr/local/lib
            )

ENDIF()