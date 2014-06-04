include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUONINPUT_INCLUDES}
    ${GLUON_PLAYER_INCLUDE_DIRS}
)

# Required Qt5 components to build this framework
find_package(Qt5 REQUIRED Core Network Widgets Qml Quick Gui)
find_package(KF5Attica REQUIRED)

set(desktop_SRCS
    main.cpp
    loginform.cpp
    qtquick2controlsapplicationviewer.cpp
)

#kde4_add_app_icon(desktop_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/*/apps/gluon-player.png")
gluon_add_executable(gluonplayer-desktop ${desktop_SRCS})
    
target_link_libraries(gluonplayer-desktop ${GLUONPLAYER_LIBRARIES} ${GLUONCORE_LIBRARIES} Qt5::Core Qt5::Qml Qt5::Gui Qt5::Quick Qt5::Widgets Qt5::Network KF5::Attica)

if(NOT APPLE)
    install(TARGETS gluonplayer-desktop
            DESTINATION ${BIN_INSTALL_DIR}
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/main.qml
                  qml/AboutWindow.qml
                  qml/RegisterUser.qml
                  qml/LoginModal.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/utils/Background.qml
                  qml/utils/GluonMenuBar.qml
                  qml/utils/GluonStatusBar.qml
                  qml/utils/GluonModalDialog.qml
                  qml/utils/Design.qml
                  qml/utils/DesignButton.qml
                  qml/utils/DesignTextField.qml
                  qml/utils/Line.qml
                  qml/utils/Box.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/utils
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/center/main.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/center
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/center/highlights/HighlightBox.qml
                  qml/center/highlights/HighlightItem.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/center/highlights
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/left/main.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/left
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/right/main.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/right
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/right/userbox/Logged.qml
                  qml/right/userbox/NotLogged.qml
            DESTINATION ${BIN_INSTALL_DIR}/qml/right/userbox
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/resources/icon.png
                  qml/resources/fav_64.png
                  qml/resources/get_64.png
                  qml/resources/home_64.png
                  qml/resources/user_64.png
            DESTINATION ${BIN_INSTALL_DIR}/qml/resources
            COMPONENT gluonplayerdesktop)
endif()
