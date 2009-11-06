cmake_minimum_required(VERSION 2.6)
project(creator_plugins)

find_package(KDE4 REQUIRED)
find_package(GluonCreator REQUIRED)
include_directories(${GLUON_CREATOR_INCLUDES})

add_subdirectory(scenedock)
add_subdirectory(projectdock)
add_subdirectory(messagedock)
