set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(WIN32)
    find_package(Glee REQUIRED)
endif(WIN32)

find_package(AssImp)

add_definitions(-DGL_GLEXT_PROTOTYPES)

gluon_include_directories(${GLUONCORE_INCLUDES} ${OPENGL_REAL_INCLUDE_DIR})

if(WIN32)
    include_directories(${GLEE_INCLUDE_DIR})
    list(APPEND GLUONGRAPHICS_INCLUDES ${GLEE_INCLUDE_DIR})
endif(WIN32)

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
    list(APPEND GLUONGRAPHICS_INCLUDES ${ASSIMP_INCLUDE_DIR})
    set(GLUON_GRAPHICS_HAS_MESH TRUE CACHE INTERNAL "")
endif(ASSIMP_FOUND)

set(GluonGraphics_SRCS
    backendcapabilities.cpp
    camera.cpp
    engine.cpp
    frustrum.cpp
    item.cpp
    material.cpp
    materialelement.cpp
    materialinstance.cpp
    mathutils.cpp
    rendertarget.cpp
    renderwidget.cpp
    technique.cpp
    texture.cpp
    abstractmesh.cpp
    vertex.cpp
    vertexattribute.cpp
    vertexbuffer.cpp
    viewport.cpp
    spritemesh.cpp
)

set(GluonGraphics_HEADERS
    backendcapabilities.h
    camera.h
    engine.h
    frustrum.h
    glheaders.h
    gluon_graphics_export.h
    item.h
    abstractmesh.h
    material.h
    materialelement.h
    materialinstance.h
    mathutils.h
    rendertarget.h
    renderwidget.h
    technique.h
    texture.h
    vertex.h
    vertexbuffer.h
    vertexattribute.h
    viewport.h
)

if(ASSIMP_FOUND)
    set( GluonGraphics_SRCS ${GluonGraphics_SRCS} filemesh.cpp )
    set( GluonGraphics_HEADERS ${GluonGraphics_HEADERS} filemesh.h )
endif(ASSIMP_FOUND)

gluon_add_library(GluonGraphics SHARED ${GluonGraphics_SRCS})
gluon_target_link_libraries(GluonGraphics ${GLUONCORE_LIBS} ${QT_QTOPENGL_LIBRARY} ${OPENGL_REAL_LIBS})

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

if(ASSIMP_FOUND)
    target_link_libraries(GluonGraphics ${ASSIMP_LIBRARY})
    list(APPEND GLUONGRAPHICS_LIBS ${ASSIMP_LIBRARY})
endif(ASSIMP_FOUND)

if(WIN32)
    target_link_libraries(GluonGraphics ${GLEE_LIBRARIES})
    list(APPEND GLUONGRAPHICS_LIBS ${GLEE_LIBRARIES})
endif(WIN32)

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    TARGETS     GluonGraphics
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluongraphics
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
    FRAMEWORK DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluongraphics
)

install(FILES
    ${GluonGraphics_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
    COMPONENT gluongraphics
)

install(
    FILES
    default.gml
    default.png
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/defaults
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

