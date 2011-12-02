include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(achievementsasset_SRCS
    achievementsasset.cpp
)

gluon_add_plugin(gluon_asset_achievements ${achievementsasset_SRCS})
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
