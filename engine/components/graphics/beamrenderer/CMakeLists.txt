include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES})

set(beamrenderercomponent_SRCS
    beamrenderercomponent.cpp
)

gluon_add_plugin(gluon_component_beamrenderer ${beamrenderercomponent_SRCS})
target_link_libraries(gluon_component_beamrenderer GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_beamrenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
