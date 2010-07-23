set(gluonviewerpart_SRCS
    gluonviewerpart.cpp
)

kde4_add_plugin(gluon_viewer_part ${gluonviewerpart_SRCS})
target_link_libraries(gluon_viewer_part ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install(TARGETS gluon_viewer_part DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_viewer_part.desktop DESTINATION ${SERVICES_INSTALL_DIR})
