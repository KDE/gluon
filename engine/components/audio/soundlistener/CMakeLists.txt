include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_AUDIO_INCLUDE_DIRS})

set(soundlistenercomponent_SRCS
    soundlistenercomponent.cpp
)

qt4_automoc(${soundlistenercomponent_SRCS})
add_library(gluon_component_soundlistener SHARED ${soundlistenercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_soundlistener GluonEngine GluonAudio)
endif()

set_target_properties(gluon_component_soundlistener PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_SOUNDLISTENER_LIB)
target_link_libraries(gluon_component_soundlistener GluonEngine ${GLUON_AUDIO_LIBS})

install(
    TARGETS
    gluon_component_soundlistener
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
