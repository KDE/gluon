include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_filemesh_SRCS
    main.cpp
)

add_executable(gluonexamples_graphics_filemesh ${gluonexamples_graphics_filemesh_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_graphics_filemesh GluonGraphics)
endif()

target_link_libraries(gluonexamples_graphics_filemesh ${GLUON_GRAPHICS_LIBS} ${QT_QTCORE_LIBRARIES})

install(TARGETS gluonexamples_graphics_filemesh RUNTIME DESTINATION ${EXAMPLES_INSTALL_DIR})
install(FILES duck.dae duck.tga DESTINATION ${EXAMPLES_DATA_INSTALL_DIR})

