project(btcomponents-testapp)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/share/kde4/apps/cmake/modules/)

find_package(Qt4 REQUIRED)
find_package(GluonCore REQUIRED)
find_package(GluonEngine REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${GLUON_ENGINE_INCLUDE_DIRS} ${GLUON_CORE_INCLUDE_DIRS})

set(btcomponents-testapp_SRCS btcomponents-testapp.cpp main.cpp)
qt4_automoc(${btcomponents-testapp_SRCS})
add_executable(btcomponents-testapp ${btcomponents-testapp_SRCS})
target_link_libraries(btcomponents-testapp ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS} ${QT_QTCORE_LIBRARY})
