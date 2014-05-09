include_directories(${GLUONINPUT_INCLUDE_DIRS})

gluon_add_plugin( gluon_component_keyboardinput GluonEngine
    SOURCES keyboardinputcomponent.cpp
    LIBRARIES ${GLUONINPUT_LIBRARIES}
)
