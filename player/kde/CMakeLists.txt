cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

set(kdeplayer_SRCS
    main.cpp
    mainwindow.cpp
)

if(APPLE)
	kde4_add_executable(gluon_kdeplayer MACOSX_BUNDLE ${kdeplayer_SRCS})
	#MACOSX_BUNDLE_INFO_STRING
	#MACOSX_BUNDLE_ICON_FILE
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
	#MACOSX_BUNDLE_COPYRIGHT

	add_custom_command(TARGET gluon_deplayer
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/core/$(CONFIGURATION)/GluonCore.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/audio/$(CONFIGURATION)/GluonAudio.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/input/$(CONFIGURATION)/GluonInput.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/graphics/$(CONFIGURATION)/GluonGraphics.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/$(CONFIGURATION)/GluonEngine.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/audio/sound/$(CONFIGURATION)/libgluon_asset_sound.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/graphics/texture/$(CONFIGURATION)/libgluon_asset_texture.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/other/script/$(CONFIGURATION)/libgluon_asset_script.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundemitter/$(CONFIGURATION)/libgluon_component_soundemitter.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundlistener/$(CONFIGURATION)/libgluon_component_soundlistener.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/cameracontroller/$(CONFIGURATION)/libgluon_component_cameracontroller.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/discrenderer/$(CONFIGURATION)/libgluon_component_discrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/discsectionrenderer/$(CONFIGURATION)/libgluon_component_discsectionrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/spriterenderer/$(CONFIGURATION)/libgluon_component_spriterenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/textrenderer/$(CONFIGURATION)/libgluon_component_textrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/input/keyboardinput/$(CONFIGURATION)/libgluon_component_keyboardinput.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/

		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/other/qtscript/$(CONFIGURATION)/libgluon_component_qtscript.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/other/spherecollision/$(CONFIGURATION)/libgluon_component_spherecollision.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
	)

	set_target_properties(gluon_kdeplayer PROPERTIES OUTPUT_NAME GluonPlayer)

else()
	kde4_add_app_icon(kdeplayer_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../icons/*/apps/gluon-player.png")
	kde4_add_executable(gluon_kdeplayer ${kdeplayer_SRCS})
endif()
target_link_libraries(gluon_kdeplayer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${KDE4_KIO_LIBS})

if(NOT APPLE)
    install(TARGETS gluon_kdeplayer DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
    install(FILES gluon_kdeplayer.desktop DESTINATION ${SHARE_INSTALL_DIR}/applications)
endif()
