cmake_minimum_required(VERSION 2.8)

project(gluonexamples_graphics_particles)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_particles_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_automoc(${gluonexamples_graphics_particles_SRCS})
add_executable(gluonexamples_graphics_particles ${gluonexamples_graphics_particles_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_graphics_particles GluonGraphics)
endif()

target_link_libraries(gluonexamples_graphics_particles ${GLUON_GRAPHICS_LIBS} ${QT_QTCORE_LIBRARIES})

install(TARGETS gluonexamples_graphics_particles RUNTIME DESTINATION ${EXAMPLES_INSTALL_DIR})
install(FILES example_particles.gluonmaterial DESTINATION ${EXAMPLES_DATA_INSTALL_DIR})
