project(tutorial2)
cmake_minimum_required(VERSION 2.6)

find_package(GluonGraphics REQUIRED)

include_directories(${GLUON_GRAPHICS_INCLUDES})

set(tutorial2_SRCS 
    main.cpp 
)

add_executable(tutorial2 ${tutorial2_SRCS})
target_link_libraries(tutorial2 ${GLUON_GRAPHICS_LIBS})

