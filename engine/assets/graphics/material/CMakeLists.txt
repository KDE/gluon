cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(materialasset_SRCS
    materialasset.cpp
)

qt4_automoc(${materialasset_SRCS})
add_library(gluon_asset_material SHARED ${materialasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_material GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_asset_material PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_MATERIAL_LIB)
target_link_libraries(gluon_asset_material GluonEngine ${GLUON_GRAPHICS_LIBS})

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