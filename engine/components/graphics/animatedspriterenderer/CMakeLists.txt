include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(animatedspriterenderercomponent_SRCS
    animatedspriterenderercomponent.cpp
)

qt4_automoc(${animatedspriterenderercomponent_SRCS})
add_library(gluon_component_animatedspriterenderer SHARED ${animatedspriterenderercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_animatedspriterenderer GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_component_animatedspriterenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_ANIMATEDSPRITERENDERER_LIB)
target_link_libraries(gluon_component_animatedspriterenderer GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_animatedspriterenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
