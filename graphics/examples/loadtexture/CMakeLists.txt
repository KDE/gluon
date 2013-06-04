include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_loadtexture_SRCS
    main.cpp
)

add_executable(gluonexamples_graphics_loadtexture ${gluonexamples_graphics_loadtexture_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_graphics_loadtexture GluonGraphics)
endif()

target_link_libraries(gluonexamples_graphics_loadtexture ${GLUON_GRAPHICS_LIBS} ${QT_QTCORE_LIBRARIES})

install(TARGETS gluonexamples_graphics_loadtexture RUNTIME DESTINATION ${EXAMPLES_INSTALL_DIR})
