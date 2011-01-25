cmake_minimum_required(VERSION 2.6)

project(gluonexamples_graphics_basic)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_basic_SRCS
    main.cpp
)

add_executable(gluonexamples_graphics_basic ${gluonexamples_graphics_basic_SRCS})
target_link_libraries(gluonexamples_graphics_basic ${GLUON_GRAPHICS_LIBS})

install(TARGETS gluonexamples_graphics_basic DESTINATION ${EXAMPLES_INSTALL_DIR})
