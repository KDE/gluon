find_package( Qt5Widgets REQUIRED CONFIG )
find_package( KF5 REQUIRED Parts GuiAddons WidgetsAddons KIO TextEditor XmlGui CoreAddons Service Completion I18n Config )

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

gluon_add_library( Gluon::Creator SHARED
    SOURCES ${GluonCreator_SRCS}
    HEADERS ${GluonCreator_HEADERS}
    LIBRARIES Gluon::Player KF5::GuiAddons KF5::KIOCore KF5::KIOWidgets KF5::Parts KF5::TextEditor KF5::XmlGui KF5::CoreAddons KF5::Service KF5::Completion KF5::ConfigCore KF5::I18n
)

#add_subdirectory( nodeeditor )
add_subdirectory( plugins )

gluon_add_subdirectories( tests )
