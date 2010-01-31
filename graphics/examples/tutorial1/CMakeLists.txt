project(tutorial1)

find_package(GluonGraphics REQUIRED)

include_directories(${GLUON_GRAPHICS_INCLUDES})

set(tutorial1_SRCS 
    main.cpp 
)

add_executable(tutorial1 ${tutorial1_SRCS})
target_link_libraries(tutorial1 ${GLUON_GRAPHICS_LIBRARY})

