cmake_minimum_required(VERSION 2.8)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDE_DIRS}
    ${GLUON_INPUT_INCLUDE_DIRS}
)

set(fremantle_SRCS
    gamewindowmanager.cpp
    main.cpp
)

# generate rules for building source files from the resources
QT4_ADD_RESOURCES(GLUONPLAYER-FREMANTLE_RCC_SRCS
    gluonplayer-fremantle.qrc
)

qt4_automoc(${fremantle_SRCS})

if(APPLE)
    add_executable(gluonplayer-fremantle MACOSX_BUNDLE ${fremantle_SRCS})
    #MACOSX_BUNDLE_INFO_STRING
    #MACOSX_BUNDLE_ICON_FILE
    #MACOSX_BUNDLE_GUI_IDENTIFIER
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
    #MACOSX_BUNDLE_COPYRIGHT

    add_custom_command(TARGET gluonplayer-fremantle
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

set_target_properties(gluonplayer-fremantle PROPERTIES OUTPUT_NAME GluonPlayerFremantle)

else()
    add_executable(gluonplayer-fremantle ${fremantle_SRCS} ${GLUONPLAYER-FREMANTLE_RCC_SRCS})
endif()
target_link_libraries(gluonplayer-fremantle ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_PLAYER_LIBS} ${GLUON_INPUT_LIBS} ${QT_QTDECLARATIVE_LIBRARY})

set(GLUON_DECLARATIVE_LIBS
    GluonPlayerFremantle
    ${GLUON_CORE_LIBS}
    ${QT_QTDECLARATIVE_LIBRARY}
    CACHE PATHS "Libraries required for Gluon Player (QML version)"
)

if(NOT APPLE)
    install(TARGETS gluonplayer-fremantle
            DESTINATION ${BIN_INSTALL_DIR}
            COMPONENT gluonplayerfremantle)

    install(FILES gluonplayer-fremantle.desktop
            DESTINATION ${SHARE_INSTALL_DIR}/applications
            COMPONENT gluonplayerfremantle)

    if(NOT PLAYER_ICONS_INSTALLED)
        set(PLAYER_ICONS_INSTALLED TRUE)
    endif()
endif()

