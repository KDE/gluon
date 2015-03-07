gluon_add_executable(gluonexamples_graphics_quickrenderer
    SOURCES main.cpp
    LIBRARIES Gluon::Graphics
)

install(FILES
    example.qml
    DESTINATION ${EXAMPLE_DATA_INSTALL_DIR}/graphics
)