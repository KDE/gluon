cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES} ${QT_QTSCRIPT_INCLUDES})

set(qtscriptcomponent_SRCS
    qtscriptcomponent.cpp
    
    bindings/com_trolltech_qt_gui_init.cpp
    bindings/qtscript_QVector2D.cpp
    bindings/qtscript_QVector3D.cpp
    bindings/qtscript_QVector4D.cpp
    bindings/qtscript_QColor.cpp
    bindings/qtscript_QQuaternion.cpp
)

qt4_automoc(${qtscriptcomponent_SRCS})
add_library(gluon_component_qtscript SHARED ${qtscriptcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_qtscript GluonEngine)
endif()

target_link_libraries(gluon_component_qtscript GluonEngine ${QT_QTSCRIPT_LIBRARY})

install(
    TARGETS
    gluon_component_qtscript
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)