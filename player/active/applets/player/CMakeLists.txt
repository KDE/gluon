install(DIRECTORY package/
        DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.gluonplayer-active
        COMPONENT gluonplayeractive)

install(FILES plasma-applet-gluonplayer-active.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluonplayeractive)
