include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_INPUT_INCLUDE_DIRS}
)

set(desktop_SRCS
    gamesoverlay.cpp
    gamedetailsoverlay.cpp
    loginform.cpp
    main.cpp
    mainwindow.cpp
    overlay.cpp

    delegates/achievementdelegate.cpp
    delegates/commentitemsviewdelegate.cpp
    delegates/itemsviewdelegate.cpp
    models/listmodel.cpp
    views/abstractitemview.cpp
    views/achievementsview.cpp
    views/gametextlabel.cpp
    views/newcommentform.cpp
)

if(APPLE)
	kde4_add_executable(gluonplayer-desktop MACOSX_BUNDLE ${desktop_SRCS})
    #MACOSX_BUNDLE_INFO_STRING
    #MACOSX_BUNDLE_ICON_FILE
    #MACOSX_BUNDLE_GUI_IDENTIFIER
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
	#MACOSX_BUNDLE_COPYRIGHT

	add_custom_command(TARGET gluonplayer-desktop
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/core/$(CONFIGURATION)/GluonCore.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/audio/$(CONFIGURATION)/GluonAudio.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/input/$(CONFIGURATION)/GluonInput.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/graphics/$(CONFIGURATION)/GluonGraphics.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/$(CONFIGURATION)/GluonEngine.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/audio/sound/$(CONFIGURATION)/libgluon_asset_sound.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/graphics/texture/$(CONFIGURATION)/libgluon_asset_texture.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundemitter/$(CONFIGURATION)/libgluon_component_soundemitter.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundlistener/$(CONFIGURATION)/libgluon_component_soundlistener.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/cameracontroller/$(CONFIGURATION)/libgluon_component_cameracontroller.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/spriterenderer/$(CONFIGURATION)/libgluon_component_spriterenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/input/keyboardinput/$(CONFIGURATION)/libgluon_component_keyboardinput.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/other/spherecollision/$(CONFIGURATION)/libgluon_component_spherecollision.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
	)

	set_target_properties(gluonplayer-desktop PROPERTIES OUTPUT_NAME GluonPlayerDesktop)

else()
	kde4_add_app_icon(desktop_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/*/apps/gluon-player.png")
	kde4_add_executable(gluonplayer-desktop ${desktop_SRCS})
endif()
target_link_libraries(gluonplayer-desktop ${GLUONENGINE_LIBRARIES} ${GLUONGRAPHICS_LIBRARIES} ${GLUONPLAYER_LIBRARIES} ${GLUONINPUT_LIBRARIES} ${KDE4_KIO_LIBS})

if(NOT APPLE)
    install(TARGETS gluonplayer-desktop
            DESTINATION ${BIN_INSTALL_DIR}
            COMPONENT gluonplayerdesktop)

    install(FILES ui/gluonplayer-desktopui.rc
            DESTINATION ${DATA_INSTALL_DIR}/gluonplayer-desktop
            COMPONENT gluonplayerdesktop)

    install(FILES gluonplayer-desktop.desktop
            DESTINATION ${SHARE_INSTALL_DIR}/applications
            COMPONENT gluonplayerdesktop)
endif()
