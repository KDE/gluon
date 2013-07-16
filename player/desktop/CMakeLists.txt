cmake_minimum_required(VERSION 2.8)

find_package(KDE4 REQUIRED)
find_package(KDeclarative REQUIRED)
find_package(LibAttica REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_INPUT_INCLUDE_DIRS}
    ${QT_INCLUDES}
    ${KDE4_INCLUDES}
    ${ATTICA_INCLUDE_DIRS}
    ${KDECLARATIVE_INCLUDE_DIRS} 
)

set(desktop_SRCS
    loginform.cpp
    main.cpp
    mainwindow.cpp
    registeruserform.cpp
    userbox.cpp
)

kde4_add_executable(gluonplayer-desktop ${desktop_SRCS})

target_link_libraries(gluonplayer-desktop ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_PLAYER_LIBS} ${GLUON_INPUT_LIBS} ${KDE4_KIO_LIBS} ${LIBATTICA_LIBRARIES} ${QT_QTDECLARATIVE_LIBRARY} ${QT_LIBRARIES}  ${KDECLARATIVE_LIBRARIES})

if(NOT APPLE)
    install(TARGETS gluonplayer-desktop
            DESTINATION ${BIN_INSTALL_DIR}
            COMPONENT gluonplayerdesktop)
    
    install(FILES gluonplayerdesktopui.rc
            DESTINATION ${DATA_INSTALL_DIR}/playerqmldesktop
            COMPONENT gluonplayerdesktop)
    
    install(FILES qml/main.qml
                  qml/LoginScreen.qml
                  qml/registeruser.qml
                  qml/bg.png
                  qml/BackgroundBox.qml
                  qml/Background.qml
            DESTINATION ${DATA_INSTALL_DIR}/playerqmldesktop/qml
            COMPONENT gluonplayerdesktop)
endif()
