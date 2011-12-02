include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES})

set(meshrenderercomponent_SRCS
    meshrenderercomponent.cpp
)

gluon_add_plugin(gluon_component_meshrenderer ${meshrenderercomponent_SRCS})
target_link_libraries(gluon_component_meshrenderer GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_meshrenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
