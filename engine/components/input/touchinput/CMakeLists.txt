include_directories(${GLUONINPUT_INCLUDE_DIRS})

gluon_add_plugin( gluon_component_touchinput GluonEngine
    SOURCES touchinputcomponent.cpp
    LIBRARIES ${GLUONINPUT_LIBRARIES}
)
