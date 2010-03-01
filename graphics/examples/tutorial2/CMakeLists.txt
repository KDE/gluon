cmake_minimum_required(VERSION 2.6)

project(tutorial2)
find_package(GluonGraphics REQUIRED)
find_package(Automoc4 REQUIRED)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES} ${GLUON_CORE_INCLUDES})



set(tutorial2_SRCS 
    main.cpp 
    testa.cpp
)


# add_executable(tutorial1 ${tutorial1_SRCS})
automoc4_add_executable(tutorial2 ${tutorial2_SRCS})
target_link_libraries(tutorial2  ${GLUON_GRAPHICS_LIBRARY})

