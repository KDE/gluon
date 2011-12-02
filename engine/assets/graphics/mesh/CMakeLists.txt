include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(meshasset_SRCS
    meshasset.cpp
)

gluon_add_plugin(gluon_asset_mesh ${meshasset_SRCS})
target_link_libraries(gluon_asset_mesh GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_mesh
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
