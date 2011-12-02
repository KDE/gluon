include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONAUDIO_INCLUDES})

set(soundlistenercomponent_SRCS
    soundlistenercomponent.cpp
)

gluon_add_plugin(gluon_component_soundlistener ${soundlistenercomponent_SRCS})
target_link_libraries(gluon_component_soundlistener GluonEngine ${GLUONAUDIO_LIBS})

install(
    TARGETS
    gluon_component_soundlistener
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

# if(BUILD_GLUON_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()
