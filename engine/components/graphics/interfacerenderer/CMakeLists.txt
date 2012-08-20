include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(interfacerenderercomponent_SRCS
    interfacerenderercomponent.cpp
)

qt4_automoc(${interfacerenderercomponent_SRCS})
add_library(gluon_component_interfacerenderer SHARED ${interfacerenderercomponent_SRCS})

set_target_properties(gluon_component_interfacerenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_INTERFACERENDERER_LIB)
target_link_libraries(gluon_component_interfacerenderer GluonEngine ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS})

install(
    TARGETS
    gluon_component_interfacerenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
