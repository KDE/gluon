include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONCORE_INCLUDES})

set(scriptingcomponent_SRCS
    scriptingengine.cpp
    scriptingasset.cpp
    scriptingcomponent.cpp
    scriptingcomponentprivate.cpp
)

gluon_add_plugin(gluon_component_scripting ${scriptingcomponent_SRCS})
target_link_libraries(gluon_component_scripting GluonEngine ${GLUONCORE_LIBRARIES})

install(
    TARGETS
    gluon_component_scripting
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

install(
    FILES
    scripting_template.js
    DESTINATION
    ${SHARE_INSTALL_DIR}/gluon/templates/scripting
)
