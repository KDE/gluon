cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES} ${QT_QTSCRIPT_INCLUDES})

set(scriptingcomponent_SRCS
 scriptingengine.cpp
 scriptingasset.cpp
 scriptingcomponent.cpp
 scriptingcomponentprivate.cpp
    
    bindings/com_trolltech_qt_gui_init.cpp
    bindings/qtscript_QVector2D.cpp
    bindings/qtscript_QVector3D.cpp
    bindings/qtscript_QVector4D.cpp
    bindings/qtscript_QColor.cpp
    bindings/qtscript_QQuaternion.cpp
)

qt4_automoc(${scriptingcomponent_SRCS})
add_library(gluon_component_scripting SHARED ${scriptingcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_scripting GluonEngine)
endif()

set_target_properties(gluon_component_scripting PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_scripting GluonEngine ${QT_QTSCRIPT_LIBRARY})

if(NOT APPLE AND NOT WIN32)
	install(
		TARGETS
		gluon_component_scripting
		DESTINATION
		${LIB_INSTALL_DIR}/gluon
	)

	install(
		    FILES
		    scripting_template.js
		    DESTINATION
		    ${SHARE_INSTALL_DIR}/gluon/templates/scripting
	)
endif()
