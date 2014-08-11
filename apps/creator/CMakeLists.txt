find_package( Qt5 REQUIRED Quick Widgets )
find_package( KF5 REQUIRED Declarative Config KCMUtils Parts )

# find_package(KDevPlatform 1.0.2)
# if(KDevPlatform_FOUND)
#     include_directories(${KDEVPLATFORM_INCLUDE_DIR})
# endif(KDevPlatform_FOUND)
# 
# add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(icons)

set(gluoncreator_SRCS
    main.cpp
    mainwindow.cpp

    dialogs/configdialog.cpp
    intro/dockeroverlay.cpp
)

kconfig_add_kcfg_files(gluoncreator_SRCS config/gluoncreatorsettings.kcfgc)
#kde4_add_app_icon(gluoncreator_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-gluon_creator.png")
gluon_add_executable(gluoncreator 
    SOURCES ${gluoncreator_SRCS}
    LIBRARIES Gluon::Creator Qt5::Quick KF5::Declarative KF5::ConfigCore KF5::ConfigWidgets KF5::KCMUtils KF5::Parts
)

install(FILES
    ui/gluoncreatorui.rc
    icons/gluon-creator-splash.png

    DESTINATION ${SHARE_INSTALL_DIR}/apps/gluoncreator
    COMPONENT gluoncreator
)

install(FILES
    config/gluoncreatorsettings.kcfg

    DESTINATION ${SHARE_INSTALL_DIR}/config.kcfg
    COMPONENT gluoncreator
)

install(FILES
    gluon-creator.desktop

    DESTINATION  ${SHARE_INSTALL_DIR}/applications
    COMPONENT gluoncreator
)

install(FILES
    dialogs/NewProjectDialogPage.qml
    dialogs/WelcomeDialog.qml
    dialogs/WelcomeDialogColumn.qml

    DESTINATION ${SHARE_INSTALL_DIR}/apps/gluoncreator/dialogs
)

install(FILES
    intro/Introduction.qml
    intro/IntroductionText.qml

    DESTINATION ${SHARE_INSTALL_DIR}/apps/gluoncreator/intro
)

find_package(SharedMimeInfo)
if(SHARED_MIME_INFO_FOUND)
    install(FILES
        x-gluon-mimetypes.xml

        DESTINATION ${XDG_MIME_INSTALL_DIR}
        COMPONENT gluoncreator
    )
    update_xdg_mimetypes(${XDG_MIME_INSTALL_DIR})
endif()
