cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(scriptasset_SRCS
    scriptasset.cpp
)

qt4_automoc(${scriptasset_SRCS})
add_library(gluon_asset_script SHARED ${scriptasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_script GluonEngine)
endif()

set_target_properties(gluon_asset_script PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_asset_script GluonEngine)

install(
    TARGETS
    gluon_asset_script
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    script_template.js
    DESTINATION
    ${SHARE_INSTALL_DIR}/gluon/templates/qtscript
)
