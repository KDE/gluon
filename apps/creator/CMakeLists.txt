include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${KDE4_INCLUDES}
    ${GLUONCREATOR_INCLUDES}
)

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
    dialogs/newprojectdialogpage.cpp
    dialogs/openprojectdialogpage.cpp
    dialogs/projectselectiondialog.cpp
    dialogs/recentprojectsdialogpage.cpp
)

kde4_add_kcfg_files(gluoncreator_SRCS config/gluoncreatorsettings.kcfgc)
kde4_add_app_icon(gluoncreator_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-gluon_creator.png")
gluon_add_executable(gluoncreator 
    SOURCES ${gluoncreator_SRCS}
    LIBRARIES ${GLUONCREATOR_LIBRARIES} ${KDE4_KUTILS_LIBS} ${KDE4_KFILE_LIBS}
)

install(FILES
    ui/gluoncreatorui.rc
    icons/gluon-creator-splash.png

    DESTINATION ${DATA_INSTALL_DIR}/gluoncreator
    COMPONENT gluoncreator
)

install(FILES
    config/gluoncreatorsettings.kcfg

    DESTINATION ${KCFG_INSTALL_DIR}
    COMPONENT gluoncreator
)

install(FILES
    gluon-creator.desktop

    DESTINATION  ${XDG_APPS_INSTALL_DIR}
    COMPONENT gluoncreator
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
