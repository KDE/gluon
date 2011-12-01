cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDE_DIRS})

qt4_generate_moc(main.cpp ${CMAKE_CURRENT_BINARY_DIR}/main.moc)

set(kdeplayer_SRCS
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/main.moc
)

if(WIN32)
    set_target_properties(gluonwinviewer PROPERTIES OUTPUT_NAME GluonWinViewer)
	kde4_add_executable(gluonwinviewer ${kdeplayer_SRCS})
    target_link_libraries(gluonwinviewer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${KDE4_KIO_LIBS})
    install(TARGETS gluonwinviewer
            DESTINATION ${BIN_INSTALL_DIR}
            COMPONENT gluonwinviewer)
endif()

