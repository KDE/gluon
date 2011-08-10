cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(statisticsasset_SRCS
    statisticsasset.cpp
)

qt4_automoc(${statisticsasset_SRCS})
add_library(gluon_asset_statistics SHARED ${statisticsasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_statistics GluonEngine)
endif()

set_target_properties(gluon_asset_statistics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_STATISTICS_LIB)
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
