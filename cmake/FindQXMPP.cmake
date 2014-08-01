# Find QXmpp library

#
# QXMPP_INCLUDE_DIR
# QXMPP_LIBRARIES
# QXMPP_FOUND

find_path(QXMPP_INCLUDE_DIR
    NAMES
    qxmpp/QXmppClient.h
    HINTS
    /usr/include /usr/local/include
    PATH
    ENV
)
find_library(QXMPP_LIBRARIES
    NAMES
    qxmpp0
    qxmpp
    qxmpp_d
    HINTS
    /usr/lib/x86_64-linux-gnu
    /usr/lib
)

if(QXMPP_LIBRARIES AND QXMPP_INCLUDE_DIR)
    set(QXMPP_INCLUDE_DIR
        ${QXMPP_INCLUDE_DIR}
    )
    set(QXMPP_FOUND 1)
endif()

if(QXMPP_FOUND)
    message(STATUS "Found QXmpp libraries at ${QXMPP_LIBRARIES}")
    message(STATUS "Found QXmpp headers at ${QXMPP_INCLUDE_DIR}")
else()
    if(QXMPP_FIND_REQUIRED)
        message(FATAL_ERROR "Could NOT find required QXmpp library, aborting")
    else()
        message(STATUS "Could NOT find QXmpp")
    endif()
endif()