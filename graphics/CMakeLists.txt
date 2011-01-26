cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
project(GluonGraphics)
find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(OPENGL_REAL_LIBS "")
set(OPENGL_REAL_INCLUDE_DIR "")
find_package(OpenGL)

if(NOT OPENGL_FOUND)
    #try looking for GLES
    find_package(OpenGLES2)
    if(OPENGLES_FOUND)
        set(OPENGL_REAL_INCLUDE_DIR ${OPENGLES_INCLUDE_DIR})
        set(OPENGL_REAL_LIBS ${OPENGLES_LIBRARIES})
        add_definitions(-DGLUON_GRAPHICS_GLES)
        message(STATUS "Found OpenGLES2: ${OPENGL_REAL_INCLUDE_DIR}")
    endif(OPENGLES_FOUND)
else(NOT OPENGL_FOUND)
    set(OPENGL_REAL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR})
    set(OPENGL_REAL_LIBS ${OPENGL_gl_LIBRARY})
    message(STATUS "Found OpenGL: ${OPENGL_REAL_INCLUDE_DIR}")
endif(NOT OPENGL_FOUND)

if(WIN32)
    find_package(GLEE)
    if(GLEE_FOUND STREQUAL "NO")
        message(FATAL_ERROR "Could NOT find GLee!")
    endif(GLEE_FOUND STREQUAL "NO")
endif(WIN32)

if(OPENGL_REAL_LIBS STREQUAL "" OR OPENGL_REAL_LIBS STREQUAL "")
    message(FATAL_ERROR "Could NOT find OpenGL!")
endif()

add_definitions(-DGL_GLEXT_PROTOTYPES)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${OPENGL_REAL_INCLUDE_DIR}
)

set(GLUON_GRAPHICS_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${OPENGL_REAL_INCLUDE_DIR}
    CACHE PATHS "Includes required for Gluon Graphics"
)

set(GluonGraphics_SRCS
    rendertarget.cpp
    backendcapabilities.cpp
    math.cpp
    frustrum.cpp
    material.cpp
    materialinstance.cpp
    technique.cpp
    materialelement.cpp
    camera.cpp
    renderwidget.cpp
    viewport.cpp
    vertex.cpp
    texture.cpp
    item.cpp
    engine.cpp
    mesh.cpp
    vertexattribute.cpp
    vertexbuffer.cpp
)

set(GluonGraphics_HEADERS
    backendcapabilities.h
    gluon_graphics_export.h
    camera.h
    renderwidget.h
    viewport.h
    vertex.h
    texture.h
    item.h
    engine.h
    mesh.h
    math.h
    frustrum.h
    material.h
    materialinstance.h
    technique.h
    materialelement.h
    vertexbuffer.h
    vertexattribute.h
    rendertarget.h
    glheaders.h
)

qt4_automoc(${GluonGraphics_SRCS})

if(APPLE)
	add_library(GluonGraphics SHARED ${GluonGraphics_SRCS} ${GluonGraphics_HEADERS})
else()
	add_library(GluonGraphics SHARED ${GluonGraphics_SRCS})
endif()

set_target_properties(GluonGraphics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_GRAPHICS_LIB)

if(APPLE)
	#hack for being able to set headers as public in a osx framework
	list(APPEND GluonGraphics_HEADERS
		${GluonGraphics_HEADERS}
	)

	set_target_properties(GluonGraphics PROPERTIES FRAMEWORK TRUE)
	set_target_properties(GluonGraphics PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
	set_target_properties(GluonGraphics PROPERTIES PUBLIC_HEADER "${GluonGraphics_HEADERS}")
	#add_custom_command(TARGET GluonGraphics POST_BUILD
      #COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonGraphics.framework/Headers/meshes
	  #COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/meshes/*.h ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonGraphics.framework/Headers/meshes/
      #COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonGraphics.framework/Headers/shaders
      #COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.h ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonGraphics.framework/Headers/shaders/
	#)

	set(MACOSX_FRAMEWORK_IDENTIFIER graphics)
	set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

if(GLUON_BUILD_ALL)
    add_dependencies(GluonGraphics GluonCore)
endif()

if(WIN32)
    target_link_libraries(
        GluonGraphics
        ${GLUON_CORE_LIBS}
        ${QT_QTOPENGL_LIBRARY}
        ${OPENGL_REAL_LIBS}
        ${GLEE_LIBRARIES}
    )
else(WIN32)
    target_link_libraries(
        GluonGraphics
        ${GLUON_CORE_LIBS}
        ${QT_QTOPENGL_LIBRARY}
        ${OPENGL_REAL_LIBS}
    )
endif(WIN32)

set(GLUON_GRAPHICS_LIBS
    GluonGraphics
    ${GLUON_CORE_LIBS}
    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_REAL_LIBS}
    CACHE PATHS "Libraries required for Gluon Graphics"
)

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(TARGETS GluonGraphics RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

install(FILES
    ${GluonGraphics_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
    COMPONENT Devel
)

install(
    FILES
    default.png
    default.gml
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/defaults
)
