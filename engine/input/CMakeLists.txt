gluon_add_plugin( gluonengine_inputplugin
    MODULE Gluon::Engine
    SOURCES inputplugin.cpp keyboardinputcomponent.cpp mouseinputcomponent.cpp
    LIBRARIES Gluon::Input
)