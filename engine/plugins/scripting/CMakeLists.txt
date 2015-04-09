set(scriptingcomponent_SRCS
    scriptingengine.cpp
    scriptingasset.cpp
    scriptingcomponent.cpp
    scriptingcomponentprivate.cpp
    scriptingplugin.cpp
)

gluon_add_plugin( gluonengine_scriptingplugin
    MODULE Gluon::Engine
    SOURCES ${scriptingcomponent_SRCS}
)

install( FILES scripting_template.js
    DESTINATION ${TEMPLATE_INSTALL_DIR}/scripting
    COMPONENT GluonEngine
)
