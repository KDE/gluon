
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    actions/
    core/
    graphicsitem/
    interface/
    models/
)

set(gluoncreator_nodeeditor_SRCS
    core/edge.cpp
    core/graph.cpp
    core/graphDocument.cpp
    core/node.cpp
    core/threadDocument.cpp
    core/DynamicPropertiesList.cpp

    actions/AbstractAction.cpp
    actions/AddEdge.cpp
    actions/AddNode.cpp
    actions/AddTypedNode.cpp
    actions/AlignAction.cpp
    actions/DeleteAction.cpp
    actions/MoveNode.cpp
    actions/Select.cpp

    graphicsitem/NodeItem.cpp
    graphicsitem/OrientedEdgeItem.cpp

    interface/edgepropertieswidget.cpp
    interface/GraphPropertiesWidget.cpp
    interface/GraphScene.cpp
    interface/GraphVisualEditor.cpp
    interface/NodeEditor.cpp
    interface/NodePropertiesWidget.cpp

    models/model_GraphDocument.cpp
    models/model_GraphLayers.cpp
    models/model_GraphProperties.cpp
)

kde4_add_ui_files(
    gluoncreator_nodeeditor_SRCS
    interface/EdgePropertiesWidget.ui
    interface/GraphPropertiesWidget.ui
    interface/NodePropertiesWidget.ui
)

kde4_add_library(gluoncreator_nodeeditor SHARED ${gluoncreator_nodeeditor_SRCS})
set_target_properties(gluoncreator_nodeeditor PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_NODEEDITOR_LIB PREFIX "")

target_link_libraries(gluoncreator_nodeeditor ${GLUON_CREATOR_LIBS})
set(GLUONCREATOR_NODEEDITOR_LIBS
    ${GLUON_CREATOR_LIBS}
    gluoncreator_nodeeditor
    CACHE INTERNAL "Libraries required for linking to nodeeditor"
)
