
if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_GRAPHICS_INCLUDE_DIRS})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})
set(GRAPHICS_EXAMPLES_DATA_INSTALL_DIR ${EXAMPLES_DATA_INSTALL_DIR}/graphics)

add_subdirectory(basic)
add_subdirectory(loadtexture)
if(ASSIMP_FOUND)
    add_subdirectory(filemesh)
endif(ASSIMP_FOUND)
