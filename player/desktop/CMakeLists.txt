project (gluonplayerdesktop)
 
find_package(KDE4 REQUIRED)
find_package(KDeclarative REQUIRED)

include_directories(${QT_INCLUDES} ${KDE4_INCLUDES} ${KDECLARATIVE_INCLUDE_DIRS})

set(gluonplayerdesktop_SRCS 
  main.cpp
  mainwindow.cpp
)

kde4_add_executable(gluonplayerdesktop ${gluonplayerdesktop_SRCS})
target_link_libraries(gluonplayerdesktop ${KDE4_KDEUI_LIBS} ${QT_QTDECLARATIVE_LIBRARY} ${QT_LIBRARIES}  ${KDECLARATIVE_LIBRARIES} )

install(TARGETS gluonplayerdesktop DESTINATION ${BIN_INSTALL_DIR})
install(FILES gluonplayerdesktopui.rc DESTINATION  ${BIN_INSTALL_DIR})
install(FILES qml/main.qml qml/loginscreen.qml DESTINATION  ${BIN_INSTALL_DIR}/qml)
