set(kcl_LIB_SRCS
   kclengine.cpp
joythread.cpp
joystickevent.cpp
   )

kde4_add_library(kcl SHARED ${kcl_LIB_SRCS})
set_target_properties(kcl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kcl 
                      ${KDE4_KDEUI_LIBS} )



install(TARGETS kcl ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    kclengine.h
    joythread.h
    joystickevent.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kcl COMPONENT Devel)
