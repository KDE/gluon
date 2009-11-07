include_directories(../lib)

set(GLUON_CREATOR_LIBS
    ${KDE4_KDEUI_LIBS}
    ${GLUON_LIBRARY}
    gluoncreatorlib
)

add_subdirectory(docks)
add_subdirectory(tools)
