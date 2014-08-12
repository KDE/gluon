find_package( Qt5Multimedia REQUIRED )

gluon_add_plugin(gluonaudio_decoderplugin_qtmmdecoder 
    MODULE Gluon::Audio
    SOURCES qtmmdecoder.cpp qtmmdecoderplugin.cpp
    LIBRARIES Gluon::Audio Qt5::Multimedia
)