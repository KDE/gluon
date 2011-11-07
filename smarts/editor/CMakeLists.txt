project(gluon_bteditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(KDE4 REQUIRED)


add_definitions(-DMAKE_BT_LIB ${KDE4_DEFINITIONS})
 
include_directories(${QT_INCLUDES} ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../common/)

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
 
#  qt4_wrap_ui(bteditor_UIS_H ${bteditor_UIS})
#   
#  qt4_automoc(${bteditor_SRCS})
# if(APPLE)
# 	add_executable(bteditor MACOSX_BUNDLE ${bteditor_SRCS} ${bteditor_UIS_H})
# 	#MACOSX_BUNDLE_INFO_STRING
# 	#MACOSX_BUNDLE_ICON_FILE
# 	#MACOSX_BUNDLE_GUI_IDENTIFIER
# 	#set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
# 	#set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
# 	#set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
# 	#set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
# 	#MACOSX_BUNDLE_COPYRIGHT
# 	
# 	set_target_properties(bteditor PROPERTIES OUTPUT_NAME "SMARTS Editor")
# 	
# else()
# 	add_executable(bteditor ${bteditor_SRCS} ${bteditor_UIS_H})
# endif()

kde4_add_ui_files(
    bteditor_SRCS
    bteditor.ui
)
 
kde4_add_plugin(gluon_bteditor ${bteditor_SRCS})

target_link_libraries(gluon_bteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTXML_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_INPUT_LIBS} ${GLUON_PLAYER_LIBS} ${KDE4_KIO_LIBS})


install(TARGETS gluon_bteditor
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluonbteditor)

install(FILES gluon_bteditor.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}/applications
        COMPONENT gluonbteditor)

install(FILES gluon_bteditor.rc
        DESTINATION ${DATA_INSTALL_DIR}/bteditor
        COMPONENT gluonbteditor)

