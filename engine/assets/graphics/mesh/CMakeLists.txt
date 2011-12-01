cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(meshasset_SRCS
    meshasset.cpp
)

qt4_automoc(${meshasset_SRCS})
add_library(gluon_asset_mesh SHARED ${meshasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_mesh GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_asset_mesh PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_TEXTURE_LIB)
target_link_libraries(gluon_asset_mesh GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_asset_mesh
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
