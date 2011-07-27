
if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_GRAPHICS_INCLUDES})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})

add_subdirectory(basic)
add_subdirectory(loadtexture)
if(ASSIMP_FOUND)
    add_subdirectory(filemesh)
endif(ASSIMP_FOUND)
