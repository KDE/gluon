project(tutorial3)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})
include_directories(${CMAKE_BINARY_DIR})

########### next target ###############

set(tutorial3_SRCS
    gameloop.cpp
    main.cpp
)

qt4_automoc(${tutorial3_SRCS})
add_executable(tutorial3 ${tutorial3_SRCS})
target_link_libraries(tutorial3 ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
