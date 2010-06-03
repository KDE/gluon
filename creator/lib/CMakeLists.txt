
set(libGluonCreator_SRCS
    plugin.cpp
    dockplugin.cpp
    dockmanager.cpp
    pluginmanager.cpp
    objectmanager.cpp
    historymanager.cpp
    selectionmanager.cpp
    newobjectcommand.cpp

    models/componentmodel.cpp
    models/projectmodel.cpp
    models/scenemodel.cpp

    widgets/propertywidget.cpp
    widgets/propertywidgetcontainer.cpp
    widgets/propertywidgetitem.cpp
    widgets/propertywidgetitemfactory.cpp
    widgets/nullpropertywidgetitem.cpp
    widgets/gluonobjectpropertywidgetitem.cpp
    widgets/enumpropertywidgetitem.cpp
)

qt4_automoc(${libGluonCreator_SRCS})
kde4_add_library(libGluonCreator SHARED ${libGluonCreator_SRCS})
set_target_properties(libGluonCreator PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_CREATOR_LIB PREFIX "")
if(GLUON_BUILD_ALL)
    add_dependencies(libGluonCreator GluonEngine)
endif()

target_link_libraries(libGluonCreator ${GLUON_ENGINE_LIBS} ${KDE4_KDEUI_LIBS})

set(GLUON_CREATOR_LIBS
    libGluonCreator
    ${GLUON_ENGINE_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KUTILS_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_KDEUI_LIBS}
    CACHE PATHS "Libraries required for Gluon Creator"
)

install(TARGETS libGluonCreator DESTINATION ${LIB_INSTALL_DIR})

install(FILES
    plugin.h
    dockplugin.h
    dockmanager.h
    pluginmanager.h
    historymanager.h
    selectionmanager.h
    gluoncreator_macros.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator
    COMPONENT Devel
)

install(FILES
    models/componentmodel.h
    models/projectmodel.h
    models/scenemodel.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/models
    COMPONENT Devel
)

install(FILES
    widgets/propertywidget.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/widgets
    COMPONENT Devel
)

install(FILES
    gluoncreator_plugin.desktop
    DESTINATION ${SERVICETYPES_INSTALL_DIR}
    COMPONENT Devel
)
