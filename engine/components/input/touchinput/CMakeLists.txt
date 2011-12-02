include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

set(touchinputcomponent_SRCS
    touchinputcomponent.cpp
)

gluon_add_plugin(gluon_component_touchinput SHARED ${touchinputcomponent_SRCS})
target_link_libraries(gluon_component_touchinput GluonEngine ${GLUONINPUT_LIBS})

install(
    TARGETS
    gluon_component_touchinput
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

