include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONAUDIO_INCLUDES})

set(soundemittercomponent_SRCS
    soundemittercomponent.cpp
)

gluon_add_plugin(gluon_component_soundemitter ${soundemittercomponent_SRCS})
target_link_libraries(gluon_component_soundemitter GluonEngine ${GLUONAUDIO_LIBS})

install(
    TARGETS
    gluon_component_soundemitter
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

# if(BUILD_GLUON_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()
