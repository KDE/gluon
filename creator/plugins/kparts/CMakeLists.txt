set( SERVICES_INSTALL_DIR ${SHARE_INSTALL_DIR}/kservices5 CACHE INTERNAL "The install dir for service (desktop, protocol, ...) files" )
set( XMLGUI_INSTALL_DIR ${SHARE_INSTALL_DIR}/kxmlgui5 CACHE INTERNAL "The install dir for XMLGui files" )

add_subdirectory(gluonviewerpart)
#add_subdirectory(gluoneditorpart)
#add_subdirectory(codeeditorpart)
