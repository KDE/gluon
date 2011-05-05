cmake_minimum_required(VERSION 2.6)
project(tutorial3)

find_package(GluonAudio REQUIRED)

include_directories(${GLUON_AUDIO_INCLUDES})

set(tutorial3_SRCS
    main.cpp
)

add_executable(tutorial3 ${tutorial3_SRCS})
target_link_libraries(tutorial3 ${GLUON_AUDIO_LIBS})
