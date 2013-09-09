include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( GluonCreator_SRCS
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

set( GluonCreator_HEADERS
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
    
    models/componentmodel.h
    models/projectmodel.h
    models/scenemodel.h

    widgets/propertywidget.h
)

gluon_add_library( GluonCreator SHARED 
    SOURCES ${GluonCreator_SRCS}
    HEADERS ${GluonCreator_HEADERS}
    LIBRARIES ${GLUNPLAYER_LIBRARIES} ${KDE4_KDECORE_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS}
)

install( FILES gluoncreator_plugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} COMPONENT gluoncreator )

gluon_add_subdirectories( tests )
