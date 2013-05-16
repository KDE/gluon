include_directories(${QT_QTSCRIPT_INCLUDES})

set(scriptingcomponent_SRCS
    scriptingengine.cpp
    scriptingasset.cpp
    scriptingcomponent.cpp
    scriptingcomponentprivate.cpp
)

gluon_add_plugin( gluon_component_scripting GluonEngine
    ${scriptingcomponent_SRCS}
    ${GLUONENGINE_LIBRARIES} ${QT_QTSCRIPT_LIBRARY}
)

install( FILES scripting_template.js
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/templates/scripting
    COMPONENT GluonEngine
)
