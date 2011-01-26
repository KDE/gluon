project(gluonexamples_input_qteventfilter)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})
include_directories(${CMAKE_BINARY_DIR})

########### next target ###############

set(gluonexamples_input_qteventfilter_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_automoc(${gluonexamples_input_qteventfilter_SRCS})
add_executable(gluonexamples_input_qteventfilter ${gluonexamples_input_qteventfilter_SRCS})
target_link_libraries(gluonexamples_input_qteventfilter ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
