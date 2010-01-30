project(tutorial2)

find_package(GluonAudio REQUIRED)

include_directories(${GLUON_AUDIO_INCLUDES})

set(tutorial2_SRCS 
    main.cpp 
)

add_executable(tutorial2 ${tutorial2_SRCS})
target_link_libraries(tutorial2 ${GLUON_AUDIO_LIBS})
