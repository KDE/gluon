
set(libGluonCreator_SRCS
    plugin.cpp
    dockplugin.cpp
    pluginmanager.cpp
    objectmanager.cpp
    selectionmanager.cpp

    models/componentmodel.cpp
    models/projectmodel.cpp
    models/scenemodel.cpp

    widgets/dock.cpp
    widgets/propertywidget.cpp

    widgets/propertywidgetitem.cpp
    widgets/propertywidgetitemfactory.cpp
    widgets/nullpropertywidgetitem.cpp
    widgets/gluonobjectpropertywidgetitem.cpp
)

qt4_automoc(${libGluonCreator_SRCS})
kde4_add_library(libGluonCreator SHARED ${libGluonCreator_SRCS})
set_target_properties(libGluonCreator PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL "MAKE_GLUONCREATOR" PREFIX "")
if(GLUON_BUILD_ALL)
    add_dependencies(libGluonCreator GluonEngine)
    target_link_libraries(libGluonCreator GluonEngine ${KDE4_KDEUI_LIBS})
else()
    target_link_libraries(libGluonCreator ${GLUON_ENGINE_LIBS} ${KDE4_KDEUI_LIBS})
endif()

install(TARGETS libGluonCreator DESTINATION ${LIB_INSTALL_DIR})

install(FILES
    plugin.h
    dockplugin.h
    pluginmanager.h
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
    widgets/dock.h
    widgets/propertywidget.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/widgets
    COMPONENT Devel
)

install(FILES
    gluoncreator_plugin.desktop
    DESTINATION ${SERVICETYPES_INSTALL_DIR}
    COMPONENT Devel
)

install(FILES
    cmake/FindGluonCreator.cmake
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/cmake
    COMPONENT Devel
)
