project(tutorial5)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})
include_directories(${CMAKE_BINARY_DIR})

########### next target ###############

set(tutorial5_SRCS
    main.cpp
    mainwindow.cpp
    inputeventtextedit.cpp
)

qt4_automoc(${tutorial5_SRCS})
add_executable(tutorial5 ${tutorial5_SRCS})
target_link_libraries(tutorial5 ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
