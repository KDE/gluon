add_subdirectory(graphics)

#Build Tests if KDE_TEST is on
if(KDE4_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif(KDE4_BUILD_TESTS)

set(codeeditorkpart_SRCS
  codewidgetkpart.cpp
)

kde4_add_plugin(gluon_creator_codewidgetkpart ${codeeditorkpart_SRCS})

target_link_libraries(gluon_creator_codewidgetkpart
    ${GLUONCREATOR_NODEEDITOR_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
)

################## INSTALLS ##########################

install(TARGETS gluon_creator_codewidgetkpart
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_creator_codewidgetkpart.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES nodetypes.gdl
        DESTINATION ${DATA_INSTALL_DIR}
        COMPONENT gluoncreator)


