include_directories(${GLUON_INPUT_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonexamples_input_devicesloop_SRCS
    gameloop.cpp
    main.cpp
)

qt4_automoc(${gluonexamples_input_devicesloop_SRCS})
add_executable(gluonexamples_input_devicesloop ${gluonexamples_input_devicesloop_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_input_devicesloop GluonInput)
endif()

target_link_libraries(gluonexamples_input_devicesloop ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS gluonexamples_input_devicesloop DESTINATION ${EXAMPLES_INSTALL_DIR})
