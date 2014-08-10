option( BUILD_MESH_LOADING "Build mesh loading support" OFF )

if( BUILD_MESH_LOADING )
    set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake  )
    find_package( AssImp )
endif( BUILD_MESH_LOADING )

set( GluonGraphics_SRCS
    camera.cpp
    frustrum.cpp
    entity.cpp
    material.cpp
    materialelement.cpp
    materialinstance.cpp
    mathutils.cpp
    rendertarget.cpp
    renderwindow.cpp
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
    renderchainitem.cpp
    sprite.cpp

#     qtquickrenderer.cpp
)

set( GluonGraphics_HEADERS
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
    renderwindow.h
    technique.h
    texture.h
    viewport.h
    texturedata.h
)

if( ASSIMP_FOUND )
    list( APPEND GluonGraphics_SRCS filemesh.cpp )
    list( APPEND GluonGraphics_HEADERS filemesh.h )
endif( ASSIMP_FOUND )

gluon_add_library( Gluon::Graphics SHARED
    SOURCES ${GluonGraphics_SRCS}
    HEADERS ${GluonGraphics_HEADERS}
    LIBRARIES Gluon::Core
)

if( ASSIMP_FOUND )
    target_include_directories( Gluon::Graphics ${ASSIMP_INCLUDE_DIR} )
    target_link_libraries( GluonGraphics ${ASSIMP_LIBRARY} )
endif( ASSIMP_FOUND )

if( APPLE )
    #add_subdirectory( agl )
elseif( WIN32 )
    #add_subdirectory( wgl )
elseif( UNIX )
    add_subdirectory( glx )
    #add_subdirectory( egl )
endif()

install( FILES
    resources/default.gluonmaterial
    resources/default.png
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/defaults
    COMPONENT GluonGraphics
)

gluon_add_subdirectories( examples tests )

save_status( GluonGraphics "Build mesh loading support (BUILD_MESH_LOADING): ${BUILD_MESH_LOADING}" )
