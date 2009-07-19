set(kcl_LIB_SRCS
kclinput.cpp
kclmouse.cpp
kclkeyboard.cpp
kcljoystick.cpp
kclcode.cpp
kclengine.cpp
   )

kde4_add_library(kcl SHARED ${kcl_LIB_SRCS})
set_target_properties(kcl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kcl 
                      ${KDE4_KDEUI_LIBS} )



install(TARGETS kcl ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    kclinput.h
    kclmouse.h
    kclkeyboard.h
    kcljoystick.h
    kclcode.h
    kclengine.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)
