set(gluoneditorpart_SRCS
    gluoneditorpart.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDE_DIRS})

kde4_add_plugin(gluon_editor_part ${gluoneditorpart_SRCS})
target_link_libraries(gluon_editor_part ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install(TARGETS gluon_editor_part
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_editor_part.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluoneditorpartui.rc DESTINATION ${DATA_INSTALL_DIR}/gluoneditorpart)
