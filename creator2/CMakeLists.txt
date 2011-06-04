cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCreator)
    find_package(KDE4 REQUIRED)
    find_package(KDevPlatform REQUIRED)
    find_package(GluonCore REQUIRED)
    find_package(GluonInput REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif()

# set(CMAKE_MODULE_PATH ${KDevelop_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# include (KDE4Defaults)
# include (MacroLibrary)
# include (MacroOptionalAddSubdirectory)

find_package(KDevPlatform 1.2.60 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${GLUON_ENGINE_INCLUDES}
)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DHAVE_CONFIG_H=1)

# create config.h
include (ConfigureChecks.cmake)
configure_file (config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )

macro_display_feature_log()

# add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(plugins)
add_subdirectory(icons)

set(gluoncreator_SRCS
    main.cpp
    kdevideextension.cpp
    dialogs/configdialog.cpp
    dialogs/projectselectiondialog.cpp
    dialogs/newprojectdialogpage.cpp
    dialogs/recentprojectsdialogpage.cpp
    dialogs/openprojectdialogpage.cpp
)

kde4_add_kcfg_files(gluoncreator_SRCS config/gluoncreatorsettings.kcfgc)
kde4_add_app_icon(gluoncreator_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-gluon_creator.png")
kde4_add_executable(gluoncreator ${gluoncreator_SRCS})
target_link_libraries(gluoncreator
    ${GLUON_CREATOR_LIBS}
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_SHELL_LIBRARIES}
    ${KDE4_KIO_LIBS}
    ${KDE4_KCMUTILS_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KNOTIFYCONFIG_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDE4_KUTILS_LIBS}
    ${KDE4_KFILE_LIBS}
    ${QT_QTDESIGNER_LIBRARY}
)

install(TARGETS gluoncreator DESTINATION ${BIN_INSTALL_DIR})
install(FILES ui/gluoncreatorui.rc DESTINATION ${DATA_INSTALL_DIR}/gluoncreator)
install(FILES config/gluoncreatorsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES gluon-creator.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )

find_package(SharedMimeInfo)
if(SHARED_MIME_INFO_FOUND)
    install(FILES x-gluon-mimetypes.xml DESTINATION ${XDG_MIME_INSTALL_DIR})
    update_xdg_mimetypes(${XDG_MIME_INSTALL_DIR})
endif()
