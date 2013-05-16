set(interfacerenderercomponent_SRCS
    interfacerenderercomponent.cpp
    textureimageprovider.cpp
)

gluon_add_plugin( gluon_component_interfacerenderer GluonEngine
    ${interfacerenderercomponent_SRCS}
    ${GLUONGRAPHICS_LIBRARIES} ${GLUONINPUT_LIBRARIES}
)