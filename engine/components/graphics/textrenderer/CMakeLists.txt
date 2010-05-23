cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    if(APPLE)
		find_package(Qt4 4.6 REQUIRED)
		
		find_library(GluonGraphics NAMES GluonGraphics)
		message("-- Found GluonGraphics:" ${GluonGraphics})
	else()
	    find_package(GluonGraphics REQUIRED)
	endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(textrenderercomponent_SRCS
    textrenderercomponent.cpp
)

qt4_automoc(${textrenderercomponent_SRCS})
add_library(gluon_component_textrenderer SHARED ${textrenderercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_textrenderer GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_component_textrenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_textrenderer GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_textrenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)