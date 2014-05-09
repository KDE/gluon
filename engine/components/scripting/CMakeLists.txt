include_directories(${CMAKE_CURRENT_BINARY_DIR} ${QT_QTSCRIPT_INCLUDES})

set(scriptingcomponent_SRCS
    scriptingengine.cpp
    scriptingasset.cpp
    scriptingcomponent.cpp
    scriptingcomponentprivate.cpp
)

gluon_add_plugin( gluon_component_scripting GluonEngine
    SOURCES ${scriptingcomponent_SRCS}
    LIBRARIES ${QT_QTSCRIPT_LIBRARY}
)

install( FILES scripting_template.js
    DESTINATION ${TEMPLATE_INSTALL_DIR}/scripting
    COMPONENT GluonEngine
)
