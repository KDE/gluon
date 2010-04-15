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

target_link_libraries(gluon_asset_script GluonEngine)

install(
    TARGETS
    gluon_asset_script
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    scriptasset.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/engine
    COMPONENT Devel
)