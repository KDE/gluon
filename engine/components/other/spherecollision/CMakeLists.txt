include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(spherecollisioncomponent_SRCS
    spherecollisioncomponent.cpp
)

gluon_add_plugin(gluon_component_spherecollision ${spherecollisioncomponent_SRCS})
target_link_libraries(gluon_component_spherecollision GluonEngine)

install(
    TARGETS
    gluon_component_spherecollision
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
