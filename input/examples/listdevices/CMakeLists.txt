include_directories(${GLUON_INPUT_INCLUDE_DIRS})

set(gluonexamples_input_listdevices_SRCS
    main.cpp
)

add_executable(gluonexamples_input_listdevices ${gluonexamples_input_listdevices_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_input_listdevices GluonInput)
endif()

target_link_libraries(gluonexamples_input_listdevices ${GLUONINPUT_LIBRARIES})

install(TARGETS gluonexamples_input_listdevices DESTINATION ${EXAMPLES_INSTALL_DIR})
