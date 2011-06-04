find_package(SharedMimeInfo REQUIRED)

set(gluonviewerpart_SRCS
    gluonviewerpart.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

kde4_add_plugin(gluon_viewer_part ${gluonviewerpart_SRCS})
target_link_libraries(gluon_viewer_part ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install(TARGETS gluon_viewer_part DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_viewer_part.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES gluonviewerpartui.rc DESTINATION ${DATA_INSTALL_DIR}/gluonviewerpart)
install(FILES gluonviewerpart.xml DESTINATION ${XDG_MIME_INSTALL_DIR} )
update_xdg_mimetypes( ${XDG_MIME_INSTALL_DIR} )
