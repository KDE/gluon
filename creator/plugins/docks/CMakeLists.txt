#cmake_minimum_required(VERSION 2.6)
#project(creator_plugins)

#find_package(KDE4 REQUIRED)
#find_package(GluonCreator REQUIRED)
#include_directories(${GLUON_CREATOR_INCLUDES})

include_directories(../creator)

set(GLUON_CREATOR_LIBS
    ${KDE4_KDEUI_LIBS}
    ${GLUON_LIBRARY}
    gluoncreatorlib
)

add_subdirectory(scenedock)
add_subdirectory(projectdock)
add_subdirectory(messagedock)
