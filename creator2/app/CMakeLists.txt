########### next target ###############

find_package(SharedMimeInfo REQUIRED)

set(gluoncreator2_SRCS main.cpp kdevideextension.cpp)

kde4_add_executable(gluoncreator2 ${gluoncreator2_SRCS} )

target_link_libraries(gluoncreator2
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_SHELL_LIBRARIES}
    ${KDE4_KIO_LIBS}
    ${KDE4_KCMUTILS_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KNOTIFYCONFIG_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${QT_QTDESIGNER_LIBRARY} )
install(TARGETS gluoncreator2 ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES kdevelop_attach DESTINATION bin PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ )

if (Q_WS_MAC)
	#sets MacOSX bundle properties for all targets in this cmake file
	#make those assignments target-dependent when cmake 2.6 is useful on MacOSX
	set(MACOSX_BUNDLE_BUNDLE_NAME KDevelop)
	set(MACOSX_BUNDLE_BUNDLE_VERSION "4.0")
	set(MACOSX_BUNDLE_COPYRIGHT "KDevelop Team")
endif (Q_WS_MAC)


########### install files ###############

install( PROGRAMS gluoncreator2.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES gluoncreator2rc DESTINATION ${CONFIG_INSTALL_DIR} )
install( FILES gluoncreator2ui.rc katepartui.rc gluoncreator2.notifyrc DESTINATION ${DATA_INSTALL_DIR}/gluoncreator2 )
install( FILES gluoncreator2.xml DESTINATION ${XDG_MIME_INSTALL_DIR} )
update_xdg_mimetypes( ${XDG_MIME_INSTALL_DIR} )
