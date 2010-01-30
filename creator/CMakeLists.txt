cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonCreator)
    find_package(KDE4 REQUIRED)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
endif()

include_directories(${KDE4_INCLUDES} ${GLUON_CORE_INCLUDES} ${GLUON_ENGINE_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(lib)
add_subdirectory(plugins)

set(gluoncreator_SRCS
    main.cpp
    mainwindow.cpp

    dialogs/configdialog.cpp
)

kde4_add_kcfg_files(gluoncreator_SRCS config/gluoncreatorsettings.kcfgc)
kde4_add_executable(gluoncreator ${gluoncreator_SRCS})
target_link_libraries(gluoncreator libGluonCreator ${KDE4_KUTILS_LIBS})

install(TARGETS gluoncreator DESTINATION ${BIN_INSTALL_DIR})
install(FILES ui/gluoncreatorui.rc DESTINATION ${DATA_INSTALL_DIR}/gluoncreator)
install(FILES config/gluoncreatorsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
