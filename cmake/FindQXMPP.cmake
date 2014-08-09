# Find QXmpp library

#
# QXMPP_INCLUDE_DIR
# QXMPP_LIBRARIES
# QXMPP_FOUND

find_path(QXMPP_INCLUDE_DIR
    NAMES
    QXmppClient.h
    HINTS
    /usr/include/qxmpp /usr/local/include/qxmpp
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

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QXmpp DEFAULT_MSG QXMPP_LIBRARIES QXMPP_INCLUDE_DIR)

