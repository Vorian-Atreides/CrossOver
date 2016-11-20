##
## Created by Gaston Siffert.
##

IF (APPLE)

    # Include dir
    find_path(MySQL_INCLUDE_DIR
            NAMES connection.h
            PATHS ${MYSQL_ROOT}/include /usr/local/include/cppconn
            )

    # Finally the library itself
    find_library(MySQL_LIBRARY
            NAMES mysqlcppconn
            PATHS ${MYSQL_ROOT}/lib /usr/local/lib
            )

ENDIF()

IF (UNIX)

    # Include dir
    find_path(MySQL_INCLUDE_DIR
            NAMES connection.h
            PATHS ${MYSQL_ROOT}/include /usr/include/cppconn
            )

    # Finally the library itself
    find_library(MySQL_LIBRARY
            NAMES mysqlcppconn
            PATHS ${MYSQL_ROOT}/lib /usr/lib
            )

ENDIF()