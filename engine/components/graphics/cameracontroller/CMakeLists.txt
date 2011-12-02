include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(cameracontrollercomponent_SRCS
    cameracontrollercomponent.cpp
)

gluon_add_plugin(gluon_component_cameracontroller ${cameracontrollercomponent_SRCS})
target_link_libraries(gluon_component_cameracontroller GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_cameracontroller
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
