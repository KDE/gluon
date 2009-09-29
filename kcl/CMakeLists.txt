set(kcl_LIB_SRCS
kclinputevent.cpp
kclthread.cpp
kclinput.cpp
kclmouse.cpp
kcltablet.cpp
kclkeyboard.cpp
kcljoystick.cpp
kclcode.cpp
kcldetect.cpp
kclcustominput.cpp

widgets/kclpressbutton.cpp
widgets/kclinputwidget.cpp
widgets/kclcustominputdialog.cpp
widgets/kclinfowidget.cpp
widgets/kcldevicemodel.cpp

)

kde4_add_library(kcl SHARED ${kcl_LIB_SRCS})
set_target_properties(kcl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kcl 
${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS} )



install(TARGETS kcl ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
kcl.h
kcl_export.h
kclinputevent.h
kclthread.h
kclinput.h
kclmouse.h
kcltablet.h
kclkeyboard.h
kcljoystick.h
kclcode.h
kcldetect.h
kclcustominput.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)

install(FILES
widgets/kclpressbutton.h
widgets/kclinputwidget.h
widgets/kclcustominputdialog.h
widgets/kclinfowidget.h
widgets/kcldevicemodel.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl/widgets COMPONENT Devel)

