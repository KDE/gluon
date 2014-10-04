gluon_add_plugin( gluonengine_audioplugin
    MODULE Gluon::Engine
    SOURCES audioplugin.cpp soundasset.cpp soundemittercomponent.cpp soundlistenercomponent.cpp
    LIBRARIES Gluon::Audio
)
