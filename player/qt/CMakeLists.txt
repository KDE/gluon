cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(qtplayer_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_automoc(${qtplayer_SRCS})

if(APPLE)
	set(EXAMPLES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../examples)

	add_executable(gluon_qtplayer MACOSX_BUNDLE ${qtplayer_SRCS})
	#MACOSX_BUNDLE_INFO_STRING
	#MACOSX_BUNDLE_ICON_FILE
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
	set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
	set_target_properties(GluonGraphics PROPERTIES RESOURCE "${GluonGraphics_RESOURCES}")
	#MACOSX_BUNDLE_COPYRIGHT
	
	add_custom_command(TARGET gluon_qtplayer
		#frameworks
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/core/$(CONFIGURATION)/GluonCore.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/audio/$(CONFIGURATION)/GluonAudio.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/input/$(CONFIGURATION)/GluonInput.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/graphics/$(CONFIGURATION)/GluonGraphics.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/$(CONFIGURATION)/GluonEngine.framework ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Frameworks/
		
		#assets plugins
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/audio/sound/$(CONFIGURATION)/libgluon_asset_sound.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/graphics/texture/$(CONFIGURATION)/libgluon_asset_texture.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/assets/other/script/$(CONFIGURATION)/libgluon_asset_script.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#audio plugins
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundemitter/$(CONFIGURATION)/libgluon_component_soundemitter.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/audio/soundlistener/$(CONFIGURATION)/libgluon_component_soundlistener.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#graphics plugins
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/cameracontroller/$(CONFIGURATION)/libgluon_component_cameracontroller.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/discrenderer/$(CONFIGURATION)/libgluon_component_discrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/discsectionrenderer/$(CONFIGURATION)/libgluon_component_discsectionrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/spriterenderer/$(CONFIGURATION)/libgluon_component_spriterenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/graphics/textrenderer/$(CONFIGURATION)/libgluon_component_textrenderer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#input plugins
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/input/keyboardinput/$(CONFIGURATION)/libgluon_component_keyboardinput.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#other plugins
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/other/qtscript/$(CONFIGURATION)/libgluon_component_qtscript.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/engine/components/other/spherecollision/$(CONFIGURATION)/libgluon_component_spherecollision.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#gluonplayer plugins
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_BINARY_DIR}/player/$(CONFIGURATION)/libGluonPlayer.dylib ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/PlugIns/
		
		#example games
		COMMAND mkdir ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Games/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${EXAMPLES_PATH}/invaders ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Games/
		COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude CVS -exclude .svn -exclude 'CMakeLists.txt' -resolve-src-symlinks ${EXAMPLES_PATH}/pong ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)/GluonPlayer.app/Contents/Games/
	)
	
	set_target_properties(gluon_qtplayer PROPERTIES OUTPUT_NAME GluonPlayer)
	
else()
	add_executable(gluon_qtplayer ${qtplayer_SRCS})
endif()

target_link_libraries(gluon_qtplayer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_PLAYER_LIBS})

if(APPLE)
	install(TARGETS gluon_qtplayer DESTINATION ${MAC_APPLICATIONS_PATH})
else()
	install(TARGETS gluon_qtplayer DESTINATION ${BIN_INSTALL_DIR})
endif()