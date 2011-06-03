

########### next target ###############

set(kdevsnippet_PART_SRCS
    projectdock.cpp
    designerplugin.cpp
)

kde4_add_plugin(kdevgluoncreatordesigner ${kdevsnippet_PART_SRCS})
target_link_libraries(kdevgluoncreatordesigner ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF3_LIBS} ${GLUON_CREATOR_LIBS}
kdevplatformlanguage kdevplatforminterfaces)
install( TARGETS kdevgluoncreatordesigner DESTINATION ${PLUGIN_INSTALL_DIR} )

########### install files ###############
install( FILES kdevgluoncreatordesigner.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
