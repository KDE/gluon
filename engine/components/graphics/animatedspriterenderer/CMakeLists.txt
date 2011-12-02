include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES})

set(animatedspriterenderercomponent_SRCS
    animatedspriterenderercomponent.cpp
)

gluon_add_plugin(gluon_component_animatedspriterenderer SHARED ${animatedspriterenderercomponent_SRCS})
target_link_libraries(gluon_component_animatedspriterenderer GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_animatedspriterenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
