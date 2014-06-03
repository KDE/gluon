if (QXMPP_LIBRARIES AND QXMPP_INCLUDE_DIRS)
  # in cache already
  set(QXMPP_FOUND TRUE)
else ()
  
  set(QXMPP_SEARCH_DIRS "${QXMPP_ROOT_DIR}" "/usr" "/usr/local" )
  
  find_path(QXMPP_INCLUDE_DIR QXmppClient.h PATH_SUFFIXES include/qxmpp HINTS ${QXMPP_SEARCH_DIRS})

  find_library(QXMPP_LIBRARY NAMES qxmpp qxmpp0 qxmpp_d PATH_SUFFIXES lib HINTS ${QXMPP_SEARCH_DIRS})
  
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(QXMPP DEFAULT_MSG QXMPP_INCLUDE_DIR QXMPP_LIBRARY)
endif ()
