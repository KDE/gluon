find_package(Qt5Widgets REQUIRED)
find_package(KF5Parts REQUIRED)

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

qt5_wrap_ui(
    bteditor_UISRCS
    bteditor.ui
)

gluon_add_executable(
    bteditor
    SOURCES ${bteditor_SRCS} ${bteditor_UISRCS}
    LIBRARIES KF5::Parts Gluon::Smarts
)

# if(APPLE)
#     add_executable(bteditor MACOSX_BUNDLE ${bteditor_SRCS} ${bteditor_UIS_H})
#     #MACOSX_BUNDLE_INFO_STRING
#     #MACOSX_BUNDLE_ICON_FILE
#     #MACOSX_BUNDLE_GUI_IDENTIFIER
#     #set(MACOSX_BUNDLE_LONG_VERSION_STRING ${GLUON_VERSION_STRING})
#     #set(MACOSX_BUNDLE_BUNDLE_NAME GluonPlayer)
#     #set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
#     #set(MACOSX_BUNDLE_BUNDLE_VERSION ${GLUON_VERSION_STRING})
#     #MACOSX_BUNDLE_COPYRIGHT
#
#     set_target_properties(bteditor PROPERTIES OUTPUT_NAME "SMARTS Editor")
#
# else()
#     add_executable(bteditor ${bteditor_SRCS} ${bteditor_UIS_H})
# endif()

gluon_add_plugin(
    gluon_bteditor
    SOURCES ${bteditor_SRCS} ${bteditor_UISRCS}
    LIBRARIES KF5::Parts Gluon::Smarts
)

# install(FILES gluon_bteditor.desktop
#         DESTINATION ${SERVICES_INSTALL_DIR}/applications
#         COMPONENT gluonbteditor)

# install(FILES gluon_bteditor.rc
#         DESTINATION ${DATA_INSTALL_DIR}/bteditor
#         COMPONENT gluonbteditor)
