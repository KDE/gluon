cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    if(APPLE)
		find_package(Qt4 4.6 REQUIRED)
		
		find_library(GluonAudio NAMES GluonAudio)
		message("-- Found GluonAudio:" ${GluonAudio})
	else()
		find_package(GluonAudio REQUIRED)
	endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_AUDIO_INCLUDES})

set(soundlistenercomponent_SRCS
    soundlistenercomponent.cpp
)

qt4_automoc(${soundlistenercomponent_SRCS})
add_library(gluon_component_soundlistener SHARED ${soundlistenercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_soundlistener GluonEngine GluonAudio)
endif()

set_target_properties(gluon_component_soundlistener PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_soundlistener GluonEngine ${GLUON_AUDIO_LIBS})

if(NOT APPLE AND NOT WIN32)
	install(
		TARGETS
		gluon_component_soundlistener
		DESTINATION
		${LIB_INSTALL_DIR}/gluon
	)
endif()