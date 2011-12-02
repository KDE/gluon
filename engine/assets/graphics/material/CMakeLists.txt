include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONGRAPHICS_INCLUDES})

set(materialasset_SRCS
    materialasset.cpp
)

gluon_add_plugin(gluon_asset_material ${materialasset_SRCS})
target_link_libraries(gluon_asset_material GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_material
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    material_template.gml
    animatedsprite_template.gml
    DESTINATION
    ${SHARE_INSTALL_DIR}/gluon/templates/material
)
