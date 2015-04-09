gluon_add_plugin( gluonengine_graphicsplugin
    MODULE Gluon::Engine
    LIBRARIES Gluon::Graphics
    SOURCES
        materialasset.cpp
        textureasset.cpp
        cameracontrollercomponent.cpp
        spriterenderercomponent.cpp
        graphicsplugin.cpp
)

install( FILES material_template.gluonmaterial
    DESTINATION ${TEMPLATE_INSTALL_DIR}/graphics
    COMPONENT GluonEngine
)
