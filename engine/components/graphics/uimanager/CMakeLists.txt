include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES} ${GLUONINPUT_INCLUDES})

set(uimanagercomponent_SRCS
    textureimageprovider.cpp
    uimanagercomponent.cpp
    engineaccess.cpp
    renderablescene.cpp

    uiasset.cpp
)

gluon_add_plugin(gluon_component_uimanager SHARED ${uimanagercomponent_SRCS})
target_link_libraries(gluon_component_uimanager GluonEngine ${GLUONGRAPHICS_LIBS} ${GLUONINPUT_LIBS} ${QT_QTDECLARATIVE_LIBRARY})

install(
    TARGETS
    gluon_component_uimanager
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(FILES template.qml DESTINATION ${SHARE_INSTALL_DIR}/gluon/templates/ui)
