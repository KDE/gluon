cmake_minimum_required(VERSION 2.6)

project(gluonexamples_input_keyboardloop)

include_directories(${GLUON_INPUT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_input_keyboardloop_SRCS
    gameloop.cpp
    main.cpp
)

qt4_automoc(${gluonexamples_input_keyboardloop_SRCS})
add_executable(gluonexamples_input_keyboardloop ${gluonexamples_input_keyboardloop_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_input_keyboardloop GluonInput)
endif()

target_link_libraries(gluonexamples_input_keyboardloop ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS gluonexamples_input_keyboardloop DESTINATION ${EXAMPLES_INSTALL_DIR})
