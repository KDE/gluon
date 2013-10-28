include(InstallRequiredSystemLibraries)

# Packaging options
# Component based settings
set(CPACK_COMPONENTS_ALL
    gluoncore
    gluonaudio
    gluoninput
    gluongraphics
    gluonengine
    gluonplayer
    gluonqtplayer
    gluonplayerfremantle
    gluonqtextplayer
    gluonkdeplayer
    gluonplayerdesktop
    gluonplasmoidplayer
    gluoncreator
)

# Core library
set(CPACK_COMPONENT_GLUONCORE_DISPLAY_NAME "Gluon Core Library")
set(CPACK_COMPONENT_GLUONCORE_DESCRIPTION
    "GluonCore is a thin library which
    provides the ability to serialize and deserialize very easily an object
    hierarchy."
)
set(CPACK_COMPONENT_GLUONCORE_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONCORE_INSTALL_TYPES Minimal Full)

# Audio library
set(CPACK_COMPONENT_GLUONAUDIO_DISPLAY_NAME "Gluon Audio Library")
set(CPACK_COMPONENT_GLUONAUDIO_DESCRIPTION
    "GluonAudio provides many convenience classes to easily use OpenAL in your
    game."
)
set(CPACK_COMPONENT_GLUONAUDIO_DEPENDS gluoncore)
set(CPACK_COMPONENT_GLUONAUDIO_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONAUDIO_INSTALL_TYPES Minimal Full)

# Input library
set(CPACK_COMPONENT_GLUONINPUT_DISPLAY_NAME "Gluon Input Library")
set(CPACK_COMPONENT_GLUONINPUT_DESCRIPTION
    "GluonInput provides a cross-platform way to manage and use the various
    input devices in a game."
)
set(CPACK_COMPONENT_GLUONINPUT_DEPENDS gluoncore)
set(CPACK_COMPONENT_GLUONINPUT_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONINPUT_INSTALL_TYPES Minimal Full)

# Graphics library
set(CPACK_COMPONENT_GLUONGRAPHICS_DISPLAY_NAME "Gluon Graphics Library")
set(CPACK_COMPONENT_GLUONGRAPHICS_DESCRIPTION
    "GluonGraphics is a graphics library based on OpenGL. It provides easy to
    use classes to set up OpenGL in your application."
)
set(CPACK_COMPONENT_GLUONGRAPHICS_DEPENDS gluoncore)
set(CPACK_COMPONENT_GLUONGRAPHICS_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONGRAPHICS_INSTALL_TYPES Minimal Full)

# Smarts library
set(CPACK_COMPONENT_GLUONSMARTS_DISPLAY_NAME "Gluon Smarts Library")
set(CPACK_COMPONENT_GLUONSMARTS_DESCRIPTION
    "GluonSmarts is a the artificial intelligence library for Gluon dealing with
    behavior tree, perception, brain and so forth"
)
set(CPACK_COMPONENT_GLUONSMARTS_DEPENDS gluoncore)
set(CPACK_COMPONENT_GLUONSMARTS_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONSMARTS_INSTALL_TYPES Minimal Full)

# Engine library
set(CPACK_COMPONENT_GLUONENGINE_DISPLAY_NAME "Gluon Engine Library")
set(CPACK_COMPONENT_GLUONENGINE_DESCRIPTION
    "GluonEngine provides all the necessary classes to build the structure of a
    game, like the game loop or the scene management."
)
set(CPACK_COMPONENT_GLUONENGINE_DEPENDS gluonaudio gluoninput gluongraphics)
set(CPACK_COMPONENT_GLUONENGINE_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONENGINE_INSTALL_TYPES Minimal Full)

# Player library
set(CPACK_COMPONENT_GLUONPLAYER_DISPLAY_NAME "Gluon Player Library")
set(CPACK_COMPONENT_GLUONPLAYER_DESCRIPTION
    "GluonPlayer provides all the necessary utilities to build a Gluon Player"
)
set(CPACK_COMPONENT_GLUONPLAYER_DEPENDS gluonengine)
set(CPACK_COMPONENT_GLUONPLAYER_GROUP "GLUONLIBS")
set(CPACK_COMPONENT_GLUONPLAYER_INSTALL_TYPES Minimal Full)

# Libraries
set(CPACK_COMPONENT_GROUP_GLUONLIBS_DISPLAY_NAME "Gluon Libraries")
set(CPACK_COMPONENT_GROUP_GLUONLIBS_DESCRIPTION
    "They provide functionality to assist in constructing games, and they
    provide functionality for users to interact with each other in relation to
    these games."
)

# Qt Player
set(CPACK_COMPONENT_GLUONQTPLAYER_DISPLAY_NAME "Gluon Qt Player Application")
set(CPACK_COMPONENT_GLUONQTPLAYER_DESCRIPTION
    "Gluon Qt Player Application mostly meant for debugging and simple purposes"
)
set(CPACK_COMPONENT_GLUONQTPLAYER_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONQTPLAYER_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONQTPLAYER_INSTALL_TYPES Minimal Full)

# Fremantle Player
set(CPACK_COMPONENT_GLUONPLAYERFREMANTLE_DISPLAY_NAME "Gluon Player Application for Fremantle")
set(CPACK_COMPONENT_GLUONPLAYERFREMANTLE_DESCRIPTION
    "Gluon Player Application mostly meant for Maemo5/Fremantle using plain QML
    solution"
)
set(CPACK_COMPONENT_GLUONPLAYERFREMANTLE_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONPLAYERFREMANTLE_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONPLAYERFREMANTLE_INSTALL_TYPES Full)

# Fremantle Player
set(CPACK_COMPONENT_GLUONPLAYERHARMATTAN_DISPLAY_NAME "Gluon Player Application for Harmattan")
set(CPACK_COMPONENT_GLUONPLAYERHARMATTAN_DESCRIPTION
    "Gluon Player Application mostly meant for Maemo6/Harmattan using plain QML
    solution"
)
set(CPACK_COMPONENT_GLUONPLAYERHARMATTAN_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONPLAYERHARMATTAN_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONPLAYERHARMATTAN_INSTALL_TYPES Full)

# KDE Player
set(CPACK_COMPONENT_GLUONKDEPLAYER_DISPLAY_NAME "Gluon KDE Player Application")
set(CPACK_COMPONENT_GLUONKDEPLAYER_DESCRIPTION
    "Gluon KDE Player Application mostly meant for debugging on Windows and simple purposes"
)
set(CPACK_COMPONENT_GLUONKDEPLAYER_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONKDEPLAYER_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONKDEPLAYER_INSTALL_TYPES Full)

# Desktop Player
set(CPACK_COMPONENT_GLUONPLAYERDESKTOP_DISPLAY_NAME "Gluon Desktop Player Application")
set(CPACK_COMPONENT_GLUONPLAYERDESKTOP_DESCRIPTION
    "Gluon Desktop Player Application is a full-fledged and powerful Gluon
    Player for Desktop using the KDE technology"
)
set(CPACK_COMPONENT_GLUONPLAYERDESKTOP_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONPLAYERDESKTOP_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONPLAYERDESKTOP_INSTALL_TYPES Full)

# Plasmoid Player
set(CPACK_COMPONENT_GLUONPLASMOIDPLAYER_DISPLAY_NAME "Gluon Plasmoid Player Application")
set(CPACK_COMPONENT_GLUONPLASMOIDPLAYER_DESCRIPTION
    "Gluon Plasmoid Player Application is a full-fledged and powerful Plasmoid applet "
)
set(CPACK_COMPONENT_GLUONPLASMOIDPLAYER_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONPLASMOIDPLAYER_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONPLASMOIDPLAYER_INSTALL_TYPES Full)

# Active Player
set(CPACK_COMPONENT_GLUONPLAYERACTIVE_DISPLAY_NAME "Gluon Active Player Application")
set(CPACK_COMPONENT_GLUONPLAYERACTIVE_DESCRIPTION
    "Gluon Active Player Application is a full-fledged and powerful active applet "
)
set(CPACK_COMPONENT_GLUONPLAYERACTIVE_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONPLAYERACTIVE_GROUP "GLUONPLAYERS")
set(CPACK_COMPONENT_GLUONPLAYERACTIVE_INSTALL_TYPES Full)

# Players
set(CPACK_COMPONENT_GROUP_GLUONPLAYERS_DISPLAY_NAME "Gluon Player Applications")
set(CPACK_COMPONENT_GROUP_GLUONPLAYERS_DISPLAY_DESCRIPTION "Gluon Player Applications")

# Creator
set(CPACK_COMPONENT_GLUONCREATOR_DISPLAY_NAME "Gluon Creator Application")
set(CPACK_COMPONENT_GLUONCREATOR_DESCRIPTION "Gluon Creator Application")
set(CPACK_COMPONENT_GLUONCREATOR_DEPENDS gluonplayer)
set(CPACK_COMPONENT_GLUONCREATOR_INSTALL_TYPES Full)

set(CPACK_ALL_INSTALL_TYPES Minimal Full)

# Common package generation settings
set(CPACK_PACKAGE_NAME "Gluon")
set(CPACK_PACKAGE_VENDOR "Gluon")
set(CPACK_PACKAGE_VERSION "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An open framework to create, distribute and play games")
set(CPACK_PACKAGE_FILE_NAME "Gluon-${GLUON_VERSION_STRING}")
set(CPACK_GENERATOR "RPM;DEB;TGZ;NSIS")
set(CPACK_PACKAGE_CONTACT "Laszlo Papp <lpapp@kde.org>, Arjen Hiemstra <ahiemstra@heimr.nl>")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Gluon-${GLUON_VERSION_STRING}")
set(CPACK_SOURCE_IGNORE_FILES
    "/\\\\.git/;
    /\\\\.gitignore$;
    /\\\\.reviewboardrc$;
    /\\\\astylerc$;
    /#;
    \\\\.krazy$;
    \\\\.swp$;
    \\\\.#;
    .*~;
    cscope.*"
)

# Debian package generation
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-gui (>= 4.6), libqt4-opengl (>= 4.6), libopenal1, libgles2")
set(CPACK_DEBIAN_PACKAGE_SECTION "Games")

# Rpm package generation
#set(CPACK_RPM_PACKAGE_REQUIRES "libqt-devel (>= 4.7.1)")

# Windows NSIS
#set(CPACK_NSIS_MUI_ICON "installer.ico")
#set(CPACK_NSIS_MUI_UNIICON "uninstaller.ico")
#set(CPACK_PACKAGE_ICON "installer.bmp")
#set(CPACK_NSIS_COMPRESSOR "/SOLID lzma")
#set(CPACK_NSIS_INSTALLED_ICON_NAME "")
set(CPACK_NSIS_HELP_LINK "http://gluon.gamingfreedom.org/about-gluon/contact")
set(CPACK_NSIS_URL_INFO_ABOUT "http://gluon.gamingfreedom.org/")
set(CPACK_NSIS_CONTACT "gluon@kde.org")

