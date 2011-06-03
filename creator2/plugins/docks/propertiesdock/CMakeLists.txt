set(propertiesview_SRCS
    propertiesdock.cpp
    propertiesviewplugin.cpp

    propertywidgetitems/qurlpropertywidgetitem.cpp
    propertywidgetitems/boolpropertywidgetitem.cpp
    propertywidgetitems/textpropertywidgetitem.cpp
    propertywidgetitems/intpropertywidgetitem.cpp
    propertywidgetitems/intvectorpropertywidgetitem.cpp
    propertywidgetitems/stringlistpropertywidgetitem.cpp
    propertywidgetitems/vectorpropertywidgetitem.cpp
    propertywidgetitems/qfontpropertywidgetitem.cpp
    propertywidgetitems/qsizefpropertywidgetitem.cpp
    propertywidgetitems/colorpropertywidgetitem.cpp
    propertywidgetitems/quaternionpropertywidgetitem.cpp
	propertywidgetitems/qrealpropertywidgetitem.cpp
)

kde4_add_plugin(gluon_creator_viewplugin_propertiesview ${propertiesview_SRCS})
target_link_libraries(gluon_creator_viewplugin_propertiesview ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF3_LIBS} ${GLUON_CREATOR_LIBS} kdevplatformlanguage kdevplatforminterfaces)

install(TARGETS gluon_creator_viewplugin_propertiesview DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_viewplugin_propertiesview.desktop DESTINATION ${SERVICES_INSTALL_DIR})
