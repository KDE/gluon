include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES})

set(spriterenderercomponent_SRCS
    spriterenderercomponent.cpp
)

add_library(gluon_component_spriterenderer ${spriterenderercomponent_SRCS})
target_link_libraries(gluon_component_spriterenderer GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_spriterenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
