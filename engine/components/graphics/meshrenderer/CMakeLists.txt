include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(meshrenderercomponent_SRCS
    meshrenderercomponent.cpp
)

qt4_automoc(${meshrenderercomponent_SRCS})
add_library(gluon_component_meshrenderer SHARED ${meshrenderercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_meshrenderer GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_component_meshrenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_SPRITERENDERER_LIB)
target_link_libraries(gluon_component_meshrenderer GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_meshrenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
