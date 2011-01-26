project(gluonexample_input_listdevices)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})

set(gluonexample_input_listdevices_SRCS
    main.cpp
)

add_executable(gluonexample_input_listdevices ${gluonexample_input_listdevices_SRCS})
target_link_libraries(gluonexample_input_listdevices ${GLUON_INPUT_LIBS})

