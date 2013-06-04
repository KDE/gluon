include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_graphics_basic_SRCS
    main.cpp
)

add_executable(gluonexamples_graphics_basic ${gluonexamples_graphics_basic_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_graphics_basic GluonGraphics)
endif()

target_link_libraries(gluonexamples_graphics_basic ${GLUON_GRAPHICS_LIBS} ${QT_QTCORE_LIBRARIES})

install(TARGETS gluonexamples_graphics_basic RUNTIME DESTINATION ${EXAMPLES_INSTALL_DIR})
