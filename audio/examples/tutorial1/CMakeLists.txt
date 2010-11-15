cmake_minimum_required(VERSION 2.6)
project(tutorial1)

find_package(GluonAudio REQUIRED)

include_directories(${GLUON_AUDIO_INCLUDES})

set(tutorial1_SRCS
    main.cpp
)

add_executable(tutorial1 ${tutorial1_SRCS})
target_link_libraries(tutorial1 ${GLUON_AUDIO_LIBS})
