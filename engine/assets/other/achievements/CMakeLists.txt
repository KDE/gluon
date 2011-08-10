cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(achievementsasset_SRCS
    achievementsasset.cpp
)

qt4_automoc(${achievementsasset_SRCS})
add_library(gluon_asset_achievements SHARED ${achievementsasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_achievements GluonEngine)
endif()

set_target_properties(gluon_asset_achievements PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_ACHIEVEMENTS_LIB)
target_link_libraries(gluon_asset_achievements GluonEngine)

install(
    TARGETS
    gluon_asset_achievements
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    achievements_template.gluonachievements
    DESTINATION
    ${SHARE_INSTALL_DIR}/gluon/templates/achievements
)
