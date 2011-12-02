include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(statisticsasset_SRCS
    statisticsasset.cpp
)

gluon_add_plugin(gluon_asset_statistics SHARED ${statisticsasset_SRCS})
target_link_libraries(gluon_asset_statistics GluonEngine)

install(
    TARGETS
    gluon_asset_statistics
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    statistics_template.gluonstatistics
    DESTINATION
    ${SHARE_INSTALL_DIR}/gluon/templates/statistics
)
