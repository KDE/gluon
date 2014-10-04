gluon_add_plugin( gluonengine_otherplugin
    MODULE Gluon::Engine
    SOURCES achievementsasset.cpp otherplugin.cpp spherecollisioncomponent.cpp statisticsasset.cpp statisticscomponent.cpp
)

install(
    FILES
    achievements_template.gluonachievements
    DESTINATION
    ${DATA_INSTALL_DIR}/templates/achievements
)

install(
    FILES
    statistics_template.gluonstatistics
    DESTINATION
    ${TEMPLATE_INSTALL_DIR}/statistics
)
