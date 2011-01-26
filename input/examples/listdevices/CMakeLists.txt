project(gluonexamples_input_listdevices)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})

set(gluonexamples_input_listdevices_SRCS
    main.cpp
)

add_executable(gluonexamples_input_listdevices ${gluonexamples_input_listdevices_SRCS})
target_link_libraries(gluonexamples_input_listdevices ${GLUON_INPUT_LIBS})

