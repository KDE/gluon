set(propertiesdock_SRCS
    propertiesdock.cpp
    propertiesdockplugin.cpp

    propertywidgetitems/qurlpropertywidgetitem.cpp
    propertywidgetitems/boolpropertywidgetitem.cpp
    propertywidgetitems/textpropertywidgetitem.cpp
    propertywidgetitems/intpropertywidgetitem.cpp
    propertywidgetitems/intvectorpropertywidgetitem.cpp
    propertywidgetitems/longlongpropertywidgetitem.cpp
    propertywidgetitems/stringlistpropertywidgetitem.cpp
    propertywidgetitems/vectorpropertywidgetitem.cpp
    propertywidgetitems/qfontpropertywidgetitem.cpp
    propertywidgetitems/qsizefpropertywidgetitem.cpp
    propertywidgetitems/colorpropertywidgetitem.cpp
    propertywidgetitems/quaternionpropertywidgetitem.cpp
    propertywidgetitems/qrealpropertywidgetitem.cpp
    propertywidgetitems/qvariantlistpropertywidgetitem.cpp
)

gluon_add_plugin(gluoncreator_dockplugin_propertiesdock 
    MODULE Gluon::Creator
    SOURCES ${propertiesdock_SRCS}
    LIBRARIES Gluon::Creator
)

