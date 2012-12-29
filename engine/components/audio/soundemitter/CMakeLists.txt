include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_AUDIO_INCLUDE_DIRS})

set(soundemittercomponent_SRCS
    soundemittercomponent.cpp
)

qt4_automoc(${soundemittercomponent_SRCS})
add_library(gluon_component_soundemitter SHARED ${soundemittercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_soundemitter GluonEngine GluonAudio gluon_asset_sound)
endif()

set_target_properties(gluon_component_soundemitter PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_SOUNDEMITTER_LIB)
target_link_libraries(gluon_component_soundemitter GluonEngine ${GLUON_AUDIO_LIBS} gluon_asset_sound)

install(
    TARGETS
    gluon_component_soundemitter
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
