include_directories(${GLUONINPUT_INCLUDE_DIRS})

gluon_add_plugin( gluon_component_mouseinput GluonEngine
    SOURCES mouseinputcomponent.cpp
    LIBRARIES ${GLUONINPUT_LIBRARIES}
)
