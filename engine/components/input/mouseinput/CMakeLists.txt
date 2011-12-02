set(mouseinputcomponent_SRCS
    mouseinputcomponent.cpp
)

add_library(gluon_component_mouseinput ${mouseinputcomponent_SRCS})
target_link_libraries(gluon_component_mouseinput GluonEngine ${GLUONINPUT_LIBS})

install(
    TARGETS
    gluon_component_mouseinput
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

