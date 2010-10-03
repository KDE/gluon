project(GluonCreatorCodeKpart)

cmake_minimum_required(VERSION 2.6.0)
set(KDE_MIN_VERSION "4.3")

find_package(GluonCreator REQUIRED)
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_subdirectory(graphics)

include_directories(
    ${KDE4_INCLUDES}
    ${GLUON_CREATOR_INCLUDES}
    ${QT_INCLUDES}
    ${KROSS_INCLUDES}
    Core/
    Actions/
    GraphicsItem/
    Interface/
    Models/
)

#Build Tests if KDE_TEST is on
if(KDE4_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif(KDE4_BUILD_TESTS)

# Preparando a biblioteca padr?o.

set( rocs_core_SRCS
  Core/graph.cpp
  Core/edge.cpp
  Core/graphDocument.cpp
  Core/node.cpp
  Core/DynamicPropertiesList.cpp
  Core/threadDocument.cpp
)


###################### Outros SRCS ############################
set ( rocs_actions_SRCS
  Actions/AbstractAction.cpp
  Actions/AddNode.cpp
  Actions/AddTypedNode.cpp
  Actions/AddEdge.cpp
  Actions/MoveNode.cpp
  Actions/Select.cpp
  Actions/DeleteAction.cpp
  Actions/AlignAction.cpp
)

set ( rocs_graphcisitem_SRCS
  GraphicsItem/NodeItem.cpp
  GraphicsItem/OrientedEdgeItem.cpp
)

set( rocs_interface_SRCS
  Interface/MainWindow.cpp
  Interface/GraphScene.cpp
  Interface/GraphVisualEditor.cpp
  Interface/GraphPropertiesWidget.cpp
  Interface/NodePropertiesWidget.cpp
  Interface/edgepropertieswidget.cpp
)

set( rocs_models_SRCS
  Models/model_GraphDocument.cpp
  Models/model_GraphLayers.cpp
  Models/model_GraphProperties.cpp
)


set(rocs_SRCS
  codewidgetkpart.cpp
  ${rocs_actions_SRCS}
  ${rocs_core_SRCS}
  ${rocs_graphcisitem_SRCS}
  ${rocs_interface_SRCS}
  ${rocs_models_SRCS}
)

kde4_add_ui_files(
	rocs_SRCS
	Interface/GraphPropertiesWidget.ui
	Interface/NodePropertiesWidget.ui
	Interface/EdgePropertiesWidget.ui
	Interface/AddMultiNodes.ui
)

set (QT_USE_QTSCRIPT true)


kde4_add_plugin(gluon_creator_codewidgetkpart ${rocs_SRCS} ${rocs_RCC_SRCS})

target_link_libraries(gluon_creator_codewidgetkpart
  ${KDE4_KDEUI_LIBS}
  ${KDE4_KPARTS_LIBS}
  ${KDE4_KROSSUI_LIBS}
  ${KDE4_KIO_LIBS}
  ${KDE4_KTEXTEDITOR_LIBS}
  ${QT_QTSCRIPT_LIBRARY}
  ${QT_QTSCRIPTTOOLS_LIBRARY}
  ${GLUON_CREATOR_LIBS}
)

################## INSTALLS ##########################

install( TARGETS gluon_creator_codewidgetkpart  DESTINATION ${PLUGIN_INSTALL_DIR} )

install( FILES gluon_creator_codewidgetkpart.desktop DESTINATION ${SERVICES_INSTALL_DIR} )

install (FILES nodetypes.gdl DESTINATION ${DATA_INSTALL_DIR} )


