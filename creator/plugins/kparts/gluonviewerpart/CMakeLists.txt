find_package(SharedMimeInfo REQUIRED)

set(gluonviewerpart_SRCS
    gluonviewerpart.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUONINPUT_INCLUDE_DIRS})

kde4_add_plugin(gluon_viewer_part ${gluonviewerpart_SRCS})
target_link_libraries(gluon_viewer_part ${GLUONENGINE_LIBRARIES} ${GLUONGRAPHICS_LIBRARIES} ${GLUONINPUT_LIBRARIES} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install(TARGETS gluon_viewer_part
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_viewer_part.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluonviewerpartui.rc
        DESTINATION ${DATA_INSTALL_DIR}/gluonviewerpart
        COMPONENT gluoncreator)
