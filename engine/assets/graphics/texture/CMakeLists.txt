cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(textureasset_SRCS
    textureasset.cpp
)

qt4_automoc(${textureasset_SRCS})
add_library(gluon_asset_texture SHARED ${textureasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_texture GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_asset_texture PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_TEXTURE_LIB)
target_link_libraries(gluon_asset_texture GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_texture
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
