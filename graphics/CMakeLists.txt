option( BUILD_MESH_LOADING "Build mesh loading support" OFF ) #Note: Needs to be ported

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake  )

if( BUILD_MESH_LOADING )
    find_package(AssImp)
else( BUILD_MESH_LOADING )
    set(ASSIMP_FOUND FALSE)
endif( BUILD_MESH_LOADING )

gluon_include_directories( GluonGraphics
    ${GLUONCORE_INCLUDE_DIRS}
)

if( ASSIMP_FOUND )
    include_directories( ${ASSIMP_INCLUDE_DIR} )
    list( APPEND GLUONGRAPHICS_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR} )
endif( ASSIMP_FOUND )

if( BUILD_EXAMPLES )
    add_subdirectory(examples)
endif()

set( GluonGraphics_SRCS
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
    renderchainitem.cpp
    sprite.cpp

    qtquickrenderer.cpp
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
    renderwidget.h
    technique.h
    texture.h
    viewport.h
    texturedata.h
)

if( ASSIMP_FOUND )
    list( APPEND GluonGraphics_SRCS filemesh.cpp )
    list( APPEND GluonGraphics_HEADERS filemesh.h )
endif( ASSIMP_FOUND )

gluon_add_library( GluonGraphics SHARED 
    "${GluonGraphics_SRCS}"
    "${GluonGraphics_HEADERS}"
    ${GLUONCORE_LIBRARIES} ${QT_QTDECLARATIVE_LIBRARY}
)

if( ASSIMP_FOUND )
    target_link_libraries( GluonGraphics ${ASSIMP_LIBRARY} )
    list( APPEND GLUONGRAPHICS_LIBRARIES ${ASSIMP_LIBRARY} )
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

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

save_status( GluonGraphics "Build mesh loading support (BUILD_MESH_LOADING): ${BUILD_MESH_LOADING}" )
