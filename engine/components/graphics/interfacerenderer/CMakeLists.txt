set(interfacerenderercomponent_SRCS
    interfacerenderercomponent.cpp
    textureimageprovider.cpp
)

gluon_add_plugin( gluon_component_interfacerenderer GluonEngine
    SOURCES ${interfacerenderercomponent_SRCS}
    LIBRARIES ${GLUONGRAPHICS_LIBRARIES} ${GLUONINPUT_LIBRARIES}
)
