project(bteditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

add_definitions(-DMAKE_BT_LIB)
 
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../common/)

set(bteditor_SRCS
    btavailablenodestreeview.cpp
    bttreeeditor.cpp
    projectparser.cpp
    nodetypefactory.cpp
    btpropertywidget.cpp
    btpropertywidgetitem.cpp
    btnodeeditwidget.cpp
    btnodemodel.cpp
    btbrain.cpp
    bteditor.cpp
    bteditornode.cpp
    ../common/btnode.cpp
    ../common/btnodetype.cpp
    ../common/btcharacter.cpp
    bteditornodetype.cpp
    btnodetypesmodel.cpp
    btnodetypesmodelnode.cpp
    bttreemodel.cpp
	btactionnode.cpp
	btcompositenode.cpp
	btconditionnode.cpp
	btdecoratornode.cpp
	btreferencenode.cpp
	btunusablenode.cpp
    btnewtreewizard.cpp
    treeselectordialog.cpp
	main.cpp
    modeltest.cpp
    colorgen.cpp
    images.cpp
	btqlistdelegate.cpp
	btqvariantlistwidget.cpp
    btchildlistwidget.cpp
	btparallelconditionswidget.cpp
)


set(bteditor_UIS
    bteditor.ui
)
 
qt4_wrap_ui(bteditor_UIS_H ${bteditor_UIS})
 
qt4_automoc(${bteditor_SRCS})
if(APPLE)
	add_executable(bteditor MACOSX_BUNDLE ${bteditor_SRCS} ${bteditor_UIS_H})
	#MACOSX_BUNDLE_INFO_STRING
	#MACOSX_BUNDLE_ICON_FILE
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	#set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
	#set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
	#set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
	#set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
	#MACOSX_BUNDLE_COPYRIGHT
	
	set_target_properties(bteditor PROPERTIES OUTPUT_NAME "SMARTS Editor")
	
else()
	add_executable(bteditor ${bteditor_SRCS} ${bteditor_UIS_H})
endif()
 
target_link_libraries(bteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY})
