gluon_add_plugin(gluon_asset_achievements GluonEngine
    SOURCES achievementsasset.cpp
)

install(
    FILES
    achievements_template.gluonachievements
    DESTINATION
    ${DATA_INSTALL_DIR}/templates/achievements
)
