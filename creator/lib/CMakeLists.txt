include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(libGluonCreator_SRCS
    abstractundocommand.cpp
    deleteobjectcommand.cpp
    dockmanager.cpp
    dockplugin.cpp
    filemanager.cpp
    historymanager.cpp
    newobjectcommand.cpp
    objectmanager.cpp
    plugin.cpp
    pluginmanager.cpp
    propertychangedcommand.cpp
    selectionmanager.cpp
    toolplugin.cpp

    models/componentmodel.cpp
    models/models.cpp
    models/modeltest.cpp
    models/projectmodel.cpp
    models/scenemodel.cpp

    widgets/enumpropertywidgetitem.cpp
    widgets/filearea.cpp
    widgets/gluonobjectpropertywidgetitem.cpp
    widgets/nullpropertywidgetitem.cpp
    widgets/prefabcontrols.cpp
    widgets/propertywidget.cpp
    widgets/propertywidgetcontainer.cpp
    widgets/propertywidgetitem.cpp
    widgets/propertywidgetitemfactory.cpp
    widgets/propertywidgetitemnewcustomproperty.cpp
)

qt4_automoc(${libGluonCreator_SRCS})
kde4_add_library(libGluonCreator SHARED ${libGluonCreator_SRCS})
set_target_properties(libGluonCreator PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_CREATOR_LIB PREFIX "")

if(GLUON_BUILD_ALL)
    add_dependencies(libGluonCreator GluonEngine GluonPlayer)
endif()

set(GLUON_CREATOR_LIBS
    libGluonCreator
    ${GLUON_PLAYER_LIBS}
    ${GLUON_ENGINE_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Creator"
)

target_link_libraries(libGluonCreator
    ${GLUON_ENGINE_LIBS}
    ${GLUON_PLAYER_LIBS}
    ${GLUON_CREATOR_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_KPARTS_LIBS}
)

install(
    TARGETS libGluonCreator
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluoncreator
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluoncreator
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluoncreator
)

install(FILES
    abstractundocommand.h
    deleteobjectcommand.h
    dockmanager.h
    dockplugin.h
    gluoncreator_macros.h
    historymanager.h
    newobjectcommand.h
    objectmanager.h
    plugin.h
    pluginmanager.h
    propertychangedcommand.h
    selectionmanager.h
    toolplugin.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib
    COMPONENT gluoncreator
)

install(FILES
    models/componentmodel.h
    models/projectmodel.h
    models/scenemodel.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib/models
    COMPONENT gluoncreator
)

install(FILES
    widgets/propertywidget.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/lib/widgets
    COMPONENT gluoncreator
)

install(FILES
    gluoncreator_plugin.desktop

    DESTINATION ${SERVICETYPES_INSTALL_DIR}
    COMPONENT gluoncreator
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

