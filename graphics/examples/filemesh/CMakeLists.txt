cmake_minimum_required(VERSION 2.6)

project(gluonexamples_graphics_filemesh)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_filemesh_SRCS
    main.cpp
)

add_executable(gluonexamples_graphics_filemesh ${gluonexamples_graphics_filemesh_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_graphics_filemesh GluonGraphics)
endif()

target_link_libraries(gluonexamples_graphics_filemesh ${GLUON_GRAPHICS_LIBS} ${QT_QTCORE_LIBRARIES})

install(TARGETS gluonexamples_graphics_filemesh DESTINATION ${EXAMPLES_INSTALL_DIR})
install(FILES duck.dae duck.tga DESTINATION ${SHARE_INSTALL_DIR}/gluon/examples )

