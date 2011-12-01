
if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_GRAPHICS_INCLUDE_DIRS})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})
set(EXAMPLES_DATA_INSTALL_DIR ${SHARE_INSTALL_DIR}/gluon/examples/graphics)

add_subdirectory(basic)
add_subdirectory(loadtexture)
if(ASSIMP_FOUND)
    add_subdirectory(filemesh)
endif(ASSIMP_FOUND)
