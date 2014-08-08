find_package( Qt5 REQUIRED Widgets Qml Quick )
find_package( KF5Attica REQUIRED )
find_package( QXMPP REQUIRED )

set(desktop_SRCS
    main.cpp
    singleuser.cpp
    selfuser.cpp
    xmppclient.cpp
    rosteritem.cpp
    qtquick2controlsapplicationviewer.cpp
)

include_directories(
    ${QXMPP_INCLUDE_DIR}
)

gluon_add_executable(gluonplayer-desktop
    SOURCES ${desktop_SRCS}
    LIBRARIES Gluon::Player Gluon::Engine Qt5::Qml Qt5::Quick Qt5::Widgets ${QXMPP_LIBRARIES}
)

set( DESKTOP_DATA_INSTALL_DIR ${DATA_INSTALL_DIR}/desktop )

install( FILES
    qml/main.qml
    qml/AboutWindow.qml
    qml/RegisterUser.qml
    qml/LoginModal.qml
    qml/ProfileWindow.qml
    qml/NotificationWindow.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}
    COMPONENT gluonplayer-desktop
)

install( FILES
    qml/utils/Background.qml
    qml/utils/GluonMenuBar.qml
    qml/utils/GluonStatusBar.qml
    qml/utils/GluonModalDialog.qml
    qml/utils/Design.qml
    qml/utils/DesignButton.qml
    qml/utils/DesignTextField.qml
    qml/utils/Line.qml
    qml/utils/Box.qml
    qml/utils/Heading.qml
    qml/utils/GluonTextArea.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/utils
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/center/main.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/center
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/center/gamelist/GameItem.qml
    qml/center/gamelist/DownloadableList.qml
    qml/center/gamelist/InstalledList.qml
    qml/center/gamelist/Rating.qml
    qml/center/gamelist/GameDetails.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/center/gamelist
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/center/singlegame/Game.qml
    qml/center/singlegame/AddCommentForm.qml
    qml/center/singlegame/CommentDelegate.qml
    qml/center/singlegame/CommentsView.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/center/singlegame
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/center/social/Social.qml
    qml/center/social/PersonDelegate.qml
    qml/center/social/ActivityDelegate.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/center/social
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/center/highlights/HighlightBox.qml
    qml/center/highlights/HighlightItem.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/center/highlights
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/chat/ChatWindow.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/chat
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/left/main.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/left
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/right/main.qml
    qml/right/FriendRequestDelegate.qml
    qml/right/ActivityDelegate.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/right
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/right/userbox/Logged.qml
    qml/right/userbox/NotLogged.qml
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/right/userbox
    COMPONENT gluonplayer-desktop
)

install(FILES
    qml/resources/icon.png
    qml/resources/fav_64.png
    qml/resources/get_64.png
    qml/resources/home_64.png
    qml/resources/user_64.png
    qml/resources/play_128.png
    qml/resources/download_128.png
    qml/resources/rating.png
    qml/resources/ratinggs.png
    DESTINATION ${DESKTOP_DATA_INSTALL_DIR}/resources
    COMPONENT gluonplayer-desktop
)
