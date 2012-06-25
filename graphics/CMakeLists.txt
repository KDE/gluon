cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
project(GluonGraphics)
    find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL)
find_package(AssImp)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDE_DIRS}
)

set(GLUON_GRAPHICS_INCLUDE_DIRS
    ${GLUON_CORE_INCLUDE_DIRS}
    CACHE INTERNAL "Includes required for Gluon Graphics"
)

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
    set(GLUON_GRAPHICS_INCLUDE_DIRS
        ${GLUON_GRAPHICS_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIR}
    )
    set(GLUON_GRAPHICS_HAS_MESH TRUE CACHE INTERNAL "")
endif(ASSIMP_FOUND)

set(GluonGraphics_SRCS
    camera.cpp
    frustrum.cpp
    entity.cpp
    material.cpp
    materialelement.cpp
    materialinstance.cpp
    mathutils.cpp
    rendertarget.cpp
    renderwidget.cpp
    technique.cpp
    texture.cpp
    mesh.cpp
    viewport.cpp
    spritemesh.cpp

    manager.cpp
    world.cpp
    outputsurface.cpp
    shader.cpp
    meshdata.cpp
    texturedata.cpp
)

set(GluonGraphics_HEADERS
    camera.h
    frustrum.h
    gluon_graphics_export.h
    entity.h
    mesh.h
    material.h
    materialelement.h
    materialinstance.h
    mathutils.h
    rendertarget.h
    renderwidget.h
    technique.h
    texture.h
    viewport.h
    texturedata.h
)

if(ASSIMP_FOUND)
    set( GluonGraphics_SRCS ${GluonGraphics_SRCS} filemesh.cpp )
    set( GluonGraphics_HEADERS ${GluonGraphics_HEADERS} filemesh.h )
endif(ASSIMP_FOUND)

qt4_automoc(${GluonGraphics_SRCS})
add_library(GluonGraphics SHARED ${GluonGraphics_SRCS} ${GluonGraphics_HEADERS})

set_target_properties(GluonGraphics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_GRAPHICS_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND GluonGraphics_HEADERS
            ${GluonGraphics_HEADERS}
    )

    set_target_properties(GluonGraphics PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonGraphics PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonGraphics PROPERTIES PUBLIC_HEADER "${GluonGraphics_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER graphics)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

target_link_libraries(
    GluonGraphics
    ${GLUON_CORE_LIBS}

    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_LIBRARIES}
)

set(GLUON_GRAPHICS_LIBS
    GluonGraphics
    ${GLUON_CORE_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Graphics"
)

if(ASSIMP_FOUND)
    target_link_libraries(GluonGraphics ${ASSIMP_LIBRARY})
    set(GLUON_GRAPHICS_LIBS ${GLUON_GRAPHICS_LIBS} ${ASSIMP_LIBRARY})
endif(ASSIMP_FOUND)

if( APPLE )
    #add_subdirectory( agl )
elseif( WIN32 )
    #add_subdirectory( wgl )
elseif( UNIX )
    add_subdirectory( glx )
    #add_subdirectory( egl )
endif()

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    TARGETS     GluonGraphics
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluongraphics
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
)

install(FILES
    ${GluonGraphics_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
    COMPONENT gluongraphics
)

# install(
#     FILES
#     default.gml
#     default.png
#     DESTINATION ${SHARE_INSTALL_DIR}/gluon/defaults
# )

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
