set(kcl_LIB_SRCS
kcl.cpp
kclinput.cpp
kclmouse.cpp
kcltablet.cpp
kclkeyboard.cpp
kcljoystick.cpp
kclcode.cpp
kclinfowidget.cpp
kcldevicemodel.cpp
kcldetect.cpp
kclbutton.cpp
kclvirtualinput.cpp
kclvirtualinputconfig.cpp
slidepushbutton.cpp

)

kde4_add_library(kcl SHARED ${kcl_LIB_SRCS})
set_target_properties(kcl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kcl 
${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS} )



install(TARGETS kcl ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
kcl.h
kclinput.h
kclmouse.h
kcltablet.h
kclkeyboard.h
kcljoystick.h
kclcode.h
kclinfowidget.h
kcldevicemodel.h
kcldetect.h
kclvirtualinput.h
kclvirtualinputconfig.h
kclbutton.h
slidepushbutton.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)



