set(propertiesdock_SRCS
    propertiesdock.cpp
    propertiesdockplugin.cpp
    propertychangedcommand.cpp

    propertywidgetitems/qurlpropertywidgetitem.cpp
    propertywidgetitems/boolpropertywidgetitem.cpp
    propertywidgetitems/textpropertywidgetitem.cpp
    propertywidgetitems/intpropertywidgetitem.cpp
    propertywidgetitems/vectorpropertywidgetitem.cpp
    propertywidgetitems/qfontpropertywidgetitem.cpp
    propertywidgetitems/qsizefpropertywidgetitem.cpp
    propertywidgetitems/colorpropertywidgetitem.cpp
    propertywidgetitems/quaternionpropertywidgetitem.cpp
	propertywidgetitems/qrealpropertywidgetitem.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_propertiesdock ${propertiesdock_SRCS})
target_link_libraries(gluon_creator_dockplugin_propertiesdock ${GLUON_CORE_LIBS} ${GLUON_CREATOR_LIBS})

install(FILES
    propertychangedcommand.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/creator/plugins/docks/propertiesdock
    COMPONENT Devel
)
install(TARGETS gluon_creator_dockplugin_propertiesdock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_propertiesdock.desktop DESTINATION ${SERVICES_INSTALL_DIR})
