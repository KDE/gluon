set(vcstool_SRCS
    vcstool.cpp
    vcstoolplugin.cpp
    widgets/vcscommitdialog.cpp
    widgets/vcsdiffwidget.cpp
)

kde4_add_plugin(gluon_creator_toolplugin_vcstool ${vcstool_SRCS})

find_package(KDevPlatform 1.0.2)
if(KDevPlatform_FOUND)
    target_link_libraries(gluon_creator_toolplugin_vcstool ${GLUON_CREATOR_LIBS} ${KDEVPLATFORM_VCS_LIBRARIES})
else(KDevPlatform_FOUND)
    target_link_libraries(gluon_creator_toolplugin_vcstool ${GLUON_CREATOR_LIBS})
endif(KDevPlatform_FOUND)

install(TARGETS gluon_creator_toolplugin_vcstool DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_toolplugin_vcstool.desktop DESTINATION ${SERVICES_INSTALL_DIR})
