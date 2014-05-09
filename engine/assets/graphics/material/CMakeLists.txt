gluon_add_plugin(gluon_asset_material GluonEngine
    SOURCES materialasset.cpp
    LIBRARIES ${GLUONGRAPHICS_LIBRARIES}
)

install(
    FILES
    material_template.gml
    animatedsprite_template.gml
    DESTINATION
    ${TEMPLATE_INSTALL_DIR}/material
)
