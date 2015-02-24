gluon_add_executable(gluonexamples_graphics_filemesh
    SOURCES main.cpp
    LIBRARIES Gluon::Graphics
)

install(FILES
    duck.dae
    duck.tga
    duck.gluonmaterial
    DESTINATION ${EXAMPLE_DATA_INSTALL_DIR}/graphics
)

