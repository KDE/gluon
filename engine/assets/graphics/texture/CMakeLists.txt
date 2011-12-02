include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(textureasset_SRCS
    textureasset.cpp
)

gluon_add_plugin(gluon_asset_texture ${textureasset_SRCS})
target_link_libraries(gluon_asset_texture GluonEngine ${GLUONGRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_texture
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
