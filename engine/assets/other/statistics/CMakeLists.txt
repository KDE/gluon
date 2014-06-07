gluon_add_plugin(gluon_asset_statistics
    MODULE Gluon::Engine
    SOURCES statisticsasset.cpp
)

install(
    FILES
    statistics_template.gluonstatistics
    DESTINATION
    ${TEMPLATE_INSTALL_DIR}/statistics
)
