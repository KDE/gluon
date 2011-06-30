include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(libGluonCreator_SRCS
    plugin.cpp
    dockplugin.cpp
    dockmanager.cpp
    toolplugin.cpp
    pluginmanager.cpp
    objectmanager.cpp
    historymanager.cpp
    selectionmanager.cpp
    filemanager.cpp
    abstractundocommand.cpp
    newobjectcommand.cpp
    deleteobjectcommand.cpp
    propertychangedcommand.cpp

    models/models.cpp
    models/componentmodel.cpp
    models/projectmodel.cpp
    models/scenemodel.cpp
    models/modeltest.cpp

    widgets/filearea.cpp
    widgets/propertywidget.cpp
    widgets/propertywidgetcontainer.cpp
    widgets/prefabcontrols.cpp
    widgets/propertywidgetitem.cpp
    widgets/propertywidgetitemfactory.cpp
    widgets/nullpropertywidgetitem.cpp
    widgets/gluonobjectpropertywidgetitem.cpp
    widgets/enumpropertywidgetitem.cpp
    widgets/propertywidgetitemnewcustomproperty.cpp
)

qt4_automoc(${libGluonCreator_SRCS})
kde4_add_library(libGluonCreator SHARED ${libGluonCreator_SRCS})
set_target_properties(libGluonCreator PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_CREATOR_LIB PREFIX "")
if(GLUON_BUILD_ALL)
    add_dependencies(libGluonCreator GluonEngine GluonPlayer)
endif()

target_link_libraries(libGluonCreator
    ${GLUON_ENGINE_LIBS}
    ${GLUON_PLAYER_LIBS}
    ${GLUON_CREATOR_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_KPARTS_LIBS}
)

set(GLUON_CREATOR_LIBS
    libGluonCreator
    ${GLUON_ENGINE_LIBS}
    ${GLUON_PLAYER_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Creator"
)

install(TARGETS libGluonCreator RUNTIME DESTINATION bin LIBRARY DESTINATION ${LIB_INSTALL_DIR} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})


install(FILES
    plugin.h
    dockplugin.h
    toolplugin.h
    dockmanager.h
    pluginmanager.h
    historymanager.h
    objectmanager.h
    selectionmanager.h
    gluoncreator_macros.h
    abstractundocommand.h
    newobjectcommand.h
    deleteobjectcommand.h
    propertychangedcommand.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib
    COMPONENT Devel
)

install(FILES
    models/componentmodel.h
    models/projectmodel.h
    models/scenemodel.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib/models
    COMPONENT Devel
)

install(FILES
    widgets/propertywidget.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib/widgets
    COMPONENT Devel
)

install(FILES
    gluoncreator_plugin.desktop
    DESTINATION ${SERVICETYPES_INSTALL_DIR}
    COMPONENT Devel
)
